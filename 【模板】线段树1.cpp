#include<cstdio>
#define ll long long
const int N=4e5+10;
int n,m,q,x,y;
ll a[N],tree[N],tag[N],k;
void build(int u,int l,int r){
	if(l==r){
		tree[u]=a[l];
		return;
	}
	tree[u]=0;
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	tree[u]=tree[u*2]+tree[u*2+1];
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	tree[u*2]+=tag[u]*(mid-l+1),tree[u*2+1]+=tag[u]*(r-mid);
	tag[u*2+1]+=tag[u],tag[u*2]+=tag[u],tag[u]=0;
	return;
}
void add(int u,int l,int r,int x,int y,ll k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]+=(r-l+1)*k;
		tag[u]+=k;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	add(u*2,l,mid,x,y,k);
	add(u*2+1,mid+1,r,x,y,k);
	tree[u]=tree[u*2]+tree[u*2+1];
	return;
}
ll ask(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return 0;
	if(x<=l&&y>=r)
		return tree[u];
	int mid=(l+r)/2;
	push_down(u,l,r);
	return ask(u*2,l,mid,x,y)+ask(u*2+1,mid+1,r,x,y);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	build(1,1,n);
	while(m--){
		scanf("%d",&q);
		if(q==1){
			scanf("%d%d%lld",&x,&y,&k);
			add(1,1,n,x,y,k);
		}
		else{
			scanf("%d%d",&x,&y);
			printf("%lld\n",ask(1,1,n,x,y));
		}
	}
	return 0;
}
