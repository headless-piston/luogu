#include<cstdio>
#include<algorithm>
#define ll long long
#define inf -1e18
using namespace std;
const int N=1e6+10;
int n,a[N],q,op;
ll tree[N*4],tag_add[N*4],tag_cover[N*4];
void debug(){
	for(int i=1;i<=4*n;i++)
		printf("%d ",tree[i]);
	printf("\n");
	return;
}
void push_up(int u){
	tree[u]=max(tree[u*2],tree[u*2+1]);
	return;
}
void build(int u,int l,int r){
	tag_cover[u]=inf;
	if(l==r){
		tree[u]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	push_up(u);
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	if(tag_cover[u]!=inf){
		tree[u*2]=tree[u*2+1]=tag_cover[u];
		tag_cover[u*2]=tag_cover[u*2+1]=tag_cover[u];
		tag_add[u*2]=tag_add[u*2+1]=0;
		tag_cover[u]=inf;
	}
	tree[u*2]+=tag_add[u],tree[u*2+1]+=tag_add[u];
	tag_add[u*2]+=tag_add[u],tag_add[u*2+1]+=tag_add[u];
	tag_add[u]=0;
	return;
}
void add(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]+=k;
		tag_add[u]+=k;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	add(u*2,l,mid,x,y,k);
	add(u*2+1,mid+1,r,x,y,k);
	push_up(u);
	return;
}
void cover(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]=k;
		tag_cover[u]=k;
		tag_add[u]=0;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,k);
	cover(u*2,l,mid,x,y,k);
	cover(u*2+1,mid+1,r,x,y,k);
	push_up(u);
	return;
}
ll ask(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return inf;
	if(x<=l&&y>=r)
		return tree[u];
	int mid=(l+r)/2;
	push_down(u,l,r);
	return max(ask(u*2,l,mid,x,y),ask(u*2+1,mid+1,r,x,y));
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%d",&op);
		int l,r,x;
		if(op==1){
			scanf("%d%d%d",&l,&r,&x);
			cover(1,1,n,l,r,x);
		}
		else if(op==2){
			scanf("%d%d%d",&l,&r,&x);
			add(1,1,n,l,r,x);
		}
		else{
			scanf("%d%d",&l,&r);
			printf("%lld\n",ask(1,1,n,l,r));
		}
	}
	return 0;
}
