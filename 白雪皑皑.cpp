#include<cstdio>
#include<algorithm>
#define ls u*2
#define rs u*2+1
const int N=1e6+10;
int n,m,p,q,t,tree[N*4],tag[N*4];
void push_down(int u,int l,int r){
	if(!tree[u])
		return;
	tree[ls]=tree[u],tree[rs]=tree[u];
	tree[u]=0;
	return;
}
void modify(int u,int l,int r,int x,int y,int k){
	if(x<=l&&y>=r){
		tree[u]=k;
		return;
	}
	push_down(u,l,r);
	int mid=(l+r)/2;
	if(x<=mid)
		modify(ls,l,mid,x,y,k);
	if(y>mid)
		modify(rs,mid+1,r,x,y,k);
	return;
}
int query(int u,int l,int r,int x){
	if(l==r)
		return tree[u];
	push_down(u,l,r);
	int mid=(l+r)/2;
	if(x<=mid)
		return query(ls,l,mid,x);
	else
		return query(rs,mid+1,r,x);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&p,&q);
	t=std::max(1,m-n+1);
	for(int i=t;i<=m;i++){
		int l=(i*p+q)%n+1,r=(i*q+p)%n+1;
		if(l>r)
			std::swap(l,r);
		modify(1,1,n,l,r,i);
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",query(1,1,n,i));
	return 0;
}
