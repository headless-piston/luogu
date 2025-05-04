#include<cstdio>
const int N=1e6+10;
int n,m,a[N],tot,root[N];
struct segtree{
	int ls,rs,val;
}tree[N*50];
void build(int &u,int l,int r){
	u=++tot;
	if(l==r){
		tree[u].val=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(tree[u].ls,l,mid);
	build(tree[u].rs,mid+1,r);
	return;
}
void modify(int old,int &u,int l,int r,int x,int v){
	u=++tot;
	tree[u]=tree[old];
	if(l==r){
		tree[u].val=v;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
		modify(tree[old].ls,tree[u].ls,l,mid,x,v);
	else
		modify(tree[old].rs,tree[u].rs,mid+1,r,x,v);
	return;
}
int query(int u,int l,int r,int x){
	if(l==r)
		return tree[u].val;
	int mid=(l+r)/2;
	if(x<=mid)
		return query(tree[u].ls,l,mid,x);
	else
		return query(tree[u].rs,mid+1,r,x);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(root[0],1,n);
	int verson,opt,loc,val;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&verson,&opt);
		if(opt==1){
			scanf("%d%d",&loc,&val);
			modify(root[verson],root[i],1,n,loc,val);
		}
		else{
			scanf("%d",&loc);
			printf("%d\n",query(root[verson],1,n,loc));
			root[i]=root[verson];
		}
	}
	return 0;
}
