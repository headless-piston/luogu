#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e5+10;
int n,m;
ll a[N],tree_sum[N*4],tree_max[N*4];
void build(int u,int l,int r){
	if(l==r){
		tree_sum[u]=tree_max[u]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	tree_sum[u]=tree_sum[u*2]+tree_sum[u*2+1];
	tree_max[u]=max(tree_max[u*2],tree_max[u*2+1]);
	return;
}
void update(int u,int l,int r,int x,int y){
	if(tree_max[u]<=1||x>r||y<l)
		return;
	if(l==r){
		tree_sum[u]=sqrt(tree_sum[u]);
		tree_max[u]=sqrt(tree_max[u]);
		return;
	}
	int mid=(l+r)/2;
	update(u*2,l,mid,x,y);
	update(u*2+1,mid+1,r,x,y);
	tree_sum[u]=tree_sum[u*2]+tree_sum[u*2+1];
	tree_max[u]=max(tree_max[u*2],tree_max[u*2+1]);
	return;
}
ll ask(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return 0;
	if(x<=l&&y>=r)
		return tree_sum[u];
	int mid=(l+r)/2;
	return ask(u*2,l,mid,x,y)+ask(u*2+1,mid+1,r,x,y);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int k,l,r;
		scanf("%d%d%d",&k,&l,&r);
		if(l>r)
			swap(l,r);
		if(k)
			printf("%lld\n",ask(1,1,n,l,r));
		else
			update(1,1,n,l,r);
	}
	return 0;
}
