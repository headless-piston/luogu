#include<cstdio>
#define ll long long
const int N=1e5+10;
int n,q,m,c;
ll tree[N*4],a[N],tag_add[4*N],tag_mul[4*N];
void build(int u,int l,int r){
	if(l==r){
		tree[u]=a[l]%m;
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	tree[u]=tree[u*2]+tree[u*2+1];
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	tree[u*2]=(tree[u*2]*tag_mul[u]+tag_add[u]*(mid-l+1))%m;
	tree[u*2+1]=(tree[u*2+1]*tag_mul[u]+tag_add[u]*(r-mid))%m;
	tag_mul[u*2]=tag_mul[u*2]*tag_mul[u]%m;
	tag_mul[u*2+1]=tag_mul[u*2+1]*tag_mul[u]%m;
	tag_add[u*2]=(tag_add[u*2]*tag_mul[u]+tag_add[u])%m;
	tag_add[u*2+1]=(tag_add[u*2+1]*tag_mul[u]+tag_add[u])%m;
	tag_add[u]=0,tag_mul[u]=1;
	return;
}
void add(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]=(tree[u]+(r-l+1)*k%m)%m;
		tag_add[u]=(tag_add[u]+k)%m;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	add(u*2,l,mid,x,y,k);
	add(u*2+1,mid+1,r,x,y,k);
	tree[u]=(tree[u*2]+tree[u*2+1])%m;
	return;
}
void mul(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]=tree[u]*k%m;
		tag_mul[u]=tag_mul[u]*k%m;
		tag_add[u]=tag_add[u]*k%m;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	mul(u*2,l,mid,x,y,k);
	mul(u*2+1,mid+1,r,x,y,k);
	tree[u]=(tree[u*2]+tree[u*2+1])%m;
	return;
}
int ask(int u,int l,int r,int x,int y){
	if(y<l||x>r)
		return 0;
	if(x<=l&&y>=r)
		return tree[u]%m;
	int mid=(l+r)/2;
	push_down(u,l,r);
	return (ask(u*2,l,mid,x,y)+ask(u*2+1,mid+1,r,x,y))%m;
}
int main(){
	scanf("%d%d%d",&n,&q,&m);
	for(int i=1;i<=4*n;i++)
		tag_mul[i]=1;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%d",&c);
		int x,y,k;
		if(c==1){
			scanf("%d%d%d",&x,&y,&k);
			mul(1,1,n,x,y,k);
		}
		else if(c==2){
			scanf("%d%d%d",&x,&y,&k);
			add(1,1,n,x,y,k);
		}
		else{
			scanf("%d%d",&x,&y);
			printf("%d\n",ask(1,1,n,x,y));
		}
	}
	return 0;
}
