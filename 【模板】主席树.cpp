#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int n,a[N],b[N],m,tot,root[N],maxn,minn,cnt,q;
struct Tree{
	int sum;
	int ls,rs;
}tree[N*50];
void build(int &u,int l,int r){
	u=++tot;
	if(l==r)
		return;
	int mid=(l+r)/2;
	build(tree[u].ls,l,mid);
	build(tree[u].rs,mid+1,r);
	return;
}
void modify(int old,int &u,int l,int r,int x){
	u=++tot;
	tree[u]=tree[old];
	tree[u].sum++;
	if(l==r)
		return;
	int mid=(l+r)/2;
	if(x<=mid)
		modify(tree[old].ls,tree[u].ls,l,mid,x);
	else
		modify(tree[old].rs,tree[u].rs,mid+1,r,x);
}
int query(int old,int u,int l,int r,int x){
	if(l==r)
		return l;
	int mid=(l+r)/2;
	int s=tree[tree[u].ls].sum-tree[tree[old].ls].sum;
	if(x<=s)
		return query(tree[old].ls,tree[u].ls,l,mid,x);
	else
		return query(tree[old].rs,tree[u].rs,mid+1,r,x-s);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	cnt=unique(b+1,b+n+1)-b-1;
	build(root[0],1,cnt);
	for(int i=1;i<=n;i++){
		int q=lower_bound(b+1,b+cnt+1,a[i])-b;
		modify(root[i-1],root[i],1,cnt,q);
	}
	while(m--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		int x=query(root[l-1],root[r],1,cnt,k);
		printf("%d\n",b[x]);
	}
	return 0;
}
