#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1e5+10;
int n,m,opt,a[N],tag_cover[N*4];
bool tag_reverse[N*4];
struct Tree{
	int sum,l0,r0,max0,l1,r1,max1;
}tree[N*4];
void push_up(int u,int l,int r){
	int mid=(l+r)/2;
	int len_left=mid-l+1;
	int len_right=r-mid;
	tree[u].sum=tree[u*2].sum+tree[u*2+1].sum;
	if(tree[u*2].sum==len_left)
		tree[u].l1=len_left+tree[u*2+1].l1;
	else
		tree[u].l1=tree[u*2].l1;
	if(tree[u*2].sum==0)
		tree[u].l0=len_left+tree[u*2+1].l0;
	else
		tree[u].l0=tree[u*2].l0;
	if(tree[u*2+1].sum==len_right)
		tree[u].r1=len_right+tree[u*2].r1;
	else
		tree[u].r1=tree[u*2+1].r1;
    if(tree[u*2+1].sum==0)
		tree[u].r0=len_right+tree[u*2].r0;
	else
		tree[u].r0=tree[u*2+1].r0;
	tree[u].max1=max(max(tree[u*2].max1,tree[u*2+1].max1),tree[u*2].r1+tree[u*2+1].l1);
	tree[u].max0=max(max(tree[u*2].max0,tree[u*2+1].max0),tree[u*2].r0+tree[u*2+1].l0);
}
void build(int u,int l,int r){
	if(l==r){
		tree[u].sum=a[l];
		tree[u].l1=tree[u].max1=tree[u].r1=a[l];
		tree[u].l0=tree[u].max0=tree[u].r0=a[l]^1;
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	push_up(u,l,r);
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	if(tag_cover[u]!=-1){
		tree[u*2].sum=tag_cover[u]*(mid-l+1);
		tree[u*2+1].sum=tag_cover[u]*(r-mid);
		tree[u*2].l1=tree[u*2].max1=tree[u*2].r1=tag_cover[u]*(mid-l+1);
		tree[u*2].l0=tree[u*2].max0=tree[u*2].r0=(tag_cover[u]^1)*(mid-l+1);
		tree[u*2+1].l1=tree[u*2+1].max1=tree[u*2+1].r1=tag_cover[u]*(r-mid);
		tree[u*2+1].l0=tree[u*2+1].max0=tree[u*2+1].r0=(tag_cover[u]^1)*(r-mid);
		tag_cover[u*2]=tag_cover[u*2+1]=tag_cover[u];
		tag_reverse[u*2]=tag_reverse[u*2+1]=0;
	}
	if(tag_reverse[u]==1){
		tree[u*2].sum=mid-l+1-tree[u*2].sum;
		tree[u*2+1].sum=r-mid-tree[u*2+1].sum;
		swap(tree[u*2].l1,tree[u*2].l0);
		swap(tree[u*2].r1,tree[u*2].r0);
		swap(tree[u*2].max1,tree[u*2].max0);
		swap(tree[u*2+1].l1,tree[u*2+1].l0);
		swap(tree[u*2+1].r1,tree[u*2+1].r0);
		swap(tree[u*2+1].max1,tree[u*2+1].max0);
		tag_reverse[u*2]^=1;
		tag_reverse[u*2+1]^=1;
	}
	tag_cover[u]=-1,tag_reverse[u]=0;
	return;
}
void cover(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tag_cover[u]=k;
		tree[u].sum=(r-l+1)*k;
		tree[u].l1=tree[u].r1=tree[u].max1=(r-l+1)*k;
		tree[u].l0=tree[u].r0=tree[u].max0=(r-l+1)*(k^1);
		tag_reverse[u]=0;
		return;
	}
	push_down(u,l,r);
	int mid=(l+r)/2;
	cover(u*2,l,mid,x,y,k);
	cover(u*2+1,mid+1,r,x,y,k);
	push_up(u,l,r);
	return;
}
void reverse(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tag_reverse[u]^=1;
		tree[u].sum=r-l+1-tree[u].sum;
		swap(tree[u].l1,tree[u].l0);
		swap(tree[u].r1,tree[u].r0);
		swap(tree[u].max1,tree[u].max0);
		return;
	}
	push_down(u,l,r);
	int mid=(l+r)/2;
	reverse(u*2,l,mid,x,y);
	reverse(u*2+1,mid+1,r,x,y);
	push_up(u,l,r);
	return;
}
int ask_sum(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return 0;
	if(x<=l&&y>=r)
		return tree[u].sum;
	push_down(u,l,r);
	int mid=(l+r)/2;
	return ask_sum(u*2,l,mid,x,y)+ask_sum(u*2+1,mid+1,r,x,y);
}
int ask_con(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return -1e9;
	if(x<=l&&y>=r)
		return tree[u].max1;
	push_down(u,l,r);
	int mid=(l+r)/2;
	return max(max(ask_con(u*2,l,mid,x,y),ask_con(u*2+1,mid+1,r,x,y)),min(mid-x+1,tree[u*2].r1)+min(y-mid,tree[u*2+1].l1));
}
int main(){
	memset(tag_cover,-1,sizeof(tag_cover));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	while(m--){
		int l,r;
		scanf("%d%d%d",&opt,&l,&r);
		l++,r++;
		if(opt==0)
			cover(1,1,n,l,r,0);
		else if(opt==1)
			cover(1,1,n,l,r,1);
		else if(opt==2)
			reverse(1,1,n,l,r);
		else if(opt==3)
			printf("%d\n",ask_sum(1,1,n,l,r));
		else
			printf("%d\n",ask_con(1,1,n,l,r));
	}
	return 0;
}
