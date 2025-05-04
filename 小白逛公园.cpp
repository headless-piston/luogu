#include<cstdio>
#include<algorithm>
#define inf 1e9
#define ls u*2
#define rs u*2+1
using namespace std;
const int N=5e5+10;
int n,m,a[N];
struct Tree{
	int sum,maxn,maxl,maxr;
}tree[N*4];
void push_up(int u){
	tree[u].sum=tree[ls].sum+tree[rs].sum;
	if(tree[ls].maxr<0&&tree[rs].maxl<0)
		tree[u].maxn=max(tree[ls].maxr,tree[rs].maxl);
	else{
		tree[u].maxn=0;
		tree[u].maxn+=max(tree[ls].maxr,0);
		tree[u].maxn+=max(tree[rs].maxl,0);
	}
	tree[u].maxn=max(tree[u].maxn,max(tree[ls].maxn,tree[rs].maxn));
	tree[u].maxl=max(tree[ls].maxl,tree[ls].sum+tree[rs].maxl);
	tree[u].maxr=max(tree[rs].maxr,tree[rs].sum+tree[ls].maxr);
	return;
}
void build(int u,int l,int r){
	if(l==r){
		tree[u].sum=tree[u].maxn=tree[u].maxl=tree[u].maxr=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(u);
	return;
}
void modify(int u,int l,int r,int x,int k){
	if(x>r||x<l)
		return;
	if(x==l&&x==r){
		tree[u].sum=tree[u].maxl=tree[u].maxr=tree[u].maxn=k;
		return;
	}
	int mid=(l+r)/2;
	modify(ls,l,mid,x,k);
	modify(rs,mid+1,r,x,k);
	push_up(u);
	return;
}
Tree query(int u,int l,int r,int x,int y){
	if(x<=l&&y>=r)
		return tree[u];
	int mid=(l+r)/2;
	if(x<=mid&&y>mid){
		Tree res;
		Tree res1=query(ls,l,mid,x,y),res2=query(rs,mid+1,r,x,y);
		res.sum=res1.sum+res2.sum;
		if(res1.maxr<0&&res2.maxl<0)
			res.maxn=max(res1.maxr,res2.maxl);
		else{
			res.maxn=0;
			res.maxn+=max(res1.maxr,0);
			res.maxn+=max(res2.maxl,0);
		}
		res.maxn=max(res.maxn,max(res1.maxn,res2.maxn));
		res.maxl=max(res1.maxl,res1.sum+res2.maxl);
		res.maxr=max(res2.maxr,res2.sum+res1.maxr);
		return res;
	}
	else if(x<=mid)
		return query(ls,l,mid,x,y);
	else
		return query(rs,mid+1,r,x,y);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,a,b;
		scanf("%d%d%d",&op,&a,&b);
		if(a>b&&op==1)
			swap(a,b);
		if(op==1)
			printf("%d\n",query(1,1,n,a,b).maxn);
		else
			modify(1,1,n,a,b);
	}
	return 0;
}
