#include<cstdio>
#include<algorithm>
#define ls u<<1
#define rs u<<1|1
using namespace std;
const int N=2e5+10;
int n,m,a[N];
struct segtree{
	long long sum,maxn,minn,plus_tag,div_tag;
}tree[N*4];
void push_up(int u){
	tree[u].sum=tree[ls].sum+tree[rs].sum;
	tree[u].maxn=max(tree[ls].maxn,tree[rs].maxn);
	tree[u].minn=min(tree[ls].minn,tree[rs].minn);
	return;
}
void build(int u,int l,int r){
	tree[u].div_tag=-1;
	if(l==r){
		tree[u].sum=tree[u].minn=tree[u].maxn=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(u);
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	if(tree[u].div_tag!=-1){
		tree[ls].plus_tag=tree[rs].plus_tag=0;
		tree[ls].div_tag=tree[rs].div_tag=tree[u].div_tag;
		tree[ls].maxn=tree[rs].maxn=tree[u].div_tag;
		tree[ls].minn=tree[rs].minn=tree[u].div_tag;
		tree[ls].sum=tree[u].div_tag*(mid-l+1);
		tree[rs].sum=tree[u].div_tag*(r-mid);
		tree[u].div_tag=-1;
	}
	if(tree[u].plus_tag){
		tree[ls].plus_tag+=tree[u].plus_tag;
		tree[rs].plus_tag+=tree[u].plus_tag;
		tree[ls].minn+=tree[u].plus_tag;
		tree[rs].minn+=tree[u].plus_tag;
		tree[ls].maxn+=tree[u].plus_tag;
		tree[rs].maxn+=tree[u].plus_tag;
		tree[ls].sum+=tree[u].plus_tag*(mid-l+1);
		tree[rs].sum+=tree[u].plus_tag*(r-mid);
		tree[u].plus_tag=0;
	}
	return;
}
void modify_plus(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u].sum+=1ll*(r-l+1)*k;
		tree[u].plus_tag+=k;
		tree[u].maxn+=k;
		tree[u].minn+=k;
		return;
	}
	push_down(u,l,r);
	int mid=(l+r)/2;
	modify_plus(ls,l,mid,x,y,k);
	modify_plus(rs,mid+1,r,x,y,k);
	push_up(u);
	return;
}
void modify_div(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		if(tree[u].minn/k==tree[u].maxn/k){
			tree[u].plus_tag=0;
			tree[u].minn=tree[u].maxn=tree[u].minn/k;
			tree[u].div_tag=tree[u].minn;
			tree[u].sum=tree[u].minn*(r-l+1);
			return;
		}
	}
	push_down(u,l,r);
	int mid=(l+r)/2;
	modify_div(ls,l,mid,x,y,k);
	modify_div(rs,mid+1,r,x,y,k);
	push_up(u);
	return;
}
long long query(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return 0;
	if(x<=l&&y>=r)
		return tree[u].sum;
	push_down(u,l,r);
	int mid=(l+r)/2;
	return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	int op,l,r,k;
	while(m--){
		scanf("%d%d%d",&op,&l,&r);
		if(op==3)
			printf("%lld\n",query(1,1,n,l,r));
		else{
			scanf("%d",&k);
			if(op==1)
				modify_div(1,1,n,l,r,k);
			else
				modify_plus(1,1,n,l,r,k);
		}
	}
	return 0;
}
