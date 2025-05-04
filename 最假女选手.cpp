#include<cstdio>
#include<algorithm>
#define ls u*2
#define rs u*2+1
#define inf 2e9
using namespace std;
const int N=5e5+10;
int n,a[N],m;
struct segment_tree{
	long long sum;
	int maxn,minn,max_se,min_se,max_cnt,min_cnt,add_tag,max_tag,min_tag;
}tree[N*4];
void push_up(int u){
	tree[u].sum=tree[ls].sum+tree[rs].sum;
	if(tree[ls].maxn==tree[rs].maxn){
		tree[u].maxn=tree[ls].maxn;
		tree[u].max_cnt=tree[ls].max_cnt+tree[rs].max_cnt;
		tree[u].max_se=max(tree[ls].max_se,tree[rs].max_se);
	}
	else if(tree[ls].maxn<tree[rs].maxn){
		tree[u].maxn=tree[rs].maxn;
		tree[u].max_cnt=tree[rs].max_cnt;
		tree[u].max_se=max(tree[ls].maxn,tree[rs].max_se);
	}
	else{
		tree[u].maxn=tree[ls].maxn;
		tree[u].max_cnt=tree[ls].max_cnt;
		tree[u].max_se=max(tree[rs].maxn,tree[ls].max_se);
	}
	if(tree[ls].minn==tree[rs].minn){
		tree[u].minn=tree[ls].minn;
		tree[u].min_cnt=tree[ls].min_cnt+tree[rs].min_cnt;
		tree[u].min_se=min(tree[ls].min_se,tree[rs].min_se);
	}
	else if(tree[ls].minn<tree[rs].minn){
		tree[u].minn=tree[ls].minn;
		tree[u].min_cnt=tree[ls].min_cnt;
		tree[u].min_se=min(tree[ls].min_se,tree[rs].minn);
	}
	else{
		tree[u].minn=tree[rs].minn;
		tree[u].min_cnt=tree[rs].min_cnt;
		tree[u].min_se=min(tree[rs].min_se,tree[ls].minn);
	}
	return;
}
void build(int u,int l,int r){
	tree[u].max_tag=-inf,tree[u].min_tag=inf;
	if(l==r){
		tree[u].sum=tree[u].maxn=tree[u].minn=a[l];
		tree[u].max_cnt=tree[u].min_cnt=1;
		tree[u].max_se=-inf;
		tree[u].min_se=inf;
		return;
	}
	int mid=(l+r)/2;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(u);
	return;
}
void update_add(int u,int l,int r,int k){
	tree[u].sum+=(r-l+1ll)*k;
	tree[u].maxn+=k,tree[u].minn+=k,tree[u].add_tag+=k;
	if(tree[u].max_se!=-inf)
		tree[u].max_se+=k;
	if(tree[u].min_se!=inf)
		tree[u].min_se+=k;
	if(tree[u].max_tag!=-inf)
		tree[u].max_tag+=k;
	if(tree[u].min_tag!=inf)
		tree[u].min_tag+=k;
	return;
}
void update_min_tag(int u,int k){
	if(tree[u].maxn<=k)
		return;
	tree[u].sum+=(1ll*k-tree[u].maxn)*tree[u].max_cnt;
	if(tree[u].min_se==tree[u].maxn)
		tree[u].min_se=k;
	if(tree[u].minn==tree[u].maxn)
		tree[u].minn=k;
	if(tree[u].max_tag>k)
		tree[u].max_tag=k;
	tree[u].maxn=k,tree[u].min_tag=k;
	return;
}
void update_max_tag(int u,int k){
	if(tree[u].minn>=k)
		return;
	tree[u].sum+=(1ll*k-tree[u].minn)*tree[u].min_cnt;
	if(tree[u].max_se==tree[u].minn)
		tree[u].max_se=k;
	if(tree[u].maxn==tree[u].minn)
		tree[u].maxn=k;
	if(tree[u].min_tag<k)
		tree[u].min_tag=k;
	tree[u].minn=k,tree[u].max_tag=k;
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	if(tree[u].add_tag)
		update_add(ls,l,mid,tree[u].add_tag),update_add(rs,mid+1,r,tree[u].add_tag);
	if(tree[u].max_tag!=-inf)
		update_max_tag(ls,tree[u].max_tag),update_max_tag(rs,tree[u].max_tag);
	if(tree[u].min_tag!=inf)
		update_min_tag(ls,tree[u].min_tag),update_min_tag(rs,tree[u].min_tag);
	tree[u].add_tag=0,tree[u].max_tag=-inf,tree[u].min_tag=inf;
	return;
}
void modify_add(int u,int l,int r,int x,int y,int k){
	if(x<=l&&y>=r){
		update_add(u,l,r,k);
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	if(x<=mid)
		modify_add(ls,l,mid,x,y,k);
	if(y>mid)
		modify_add(rs,mid+1,r,x,y,k);
	push_up(u);
	return;
}
void modify_max(int u,int l,int r,int x,int y,int k){
	if(x<=l&&y>=r&&tree[u].min_se>k){
		update_max_tag(u,k);
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	if(x<=mid)
		modify_max(ls,l,mid,x,y,k);
	if(y>mid)
		modify_max(rs,mid+1,r,x,y,k);
	push_up(u);
	return;
}
void modify_min(int u,int l,int r,int x,int y,int k){
	if(x<=l&&y>=r&&tree[u].max_se<k){
		update_min_tag(u,k);
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	if(x<=mid)
		modify_min(ls,l,mid,x,y,k);
	if(y>mid)
		modify_min(rs,mid+1,r,x,y,k);
	push_up(u);
	return;
}
long long query_sum(int u,int l,int r,int x,int y){
	if(x<=l&&y>=r)
		return tree[u].sum;
	long long res=0;
	int mid=(l+r)/2;
	push_down(u,l,r);
	if(x<=mid)
		res+=query_sum(ls,l,mid,x,y);
	if(y>mid)
		res+=query_sum(rs,mid+1,r,x,y);
	return res;
}
int query_max(int u,int l,int r,int x,int y){
	if(x<=l&&y>=r)
		return tree[u].maxn;
	int res=-inf,mid=(l+r)/2;
	push_down(u,l,r);
	if(x<=mid)
		res=max(res,query_max(ls,l,mid,x,y));
	if(y>mid)
		res=max(res,query_max(rs,mid+1,r,x,y));
	return res;
}
int query_min(int u,int l,int r,int x,int y){
	if(x<=l&&y>=r)
		return tree[u].minn;
	int res=inf,mid=(l+r)/2;
	push_down(u,l,r);
	if(x<=mid)
		res=min(res,query_min(ls,l,mid,x,y));
	if(y>mid)
		res=min(res,query_min(rs,mid+1,r,x,y));
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	build(1,1,n);
	scanf("%d",&m);
	int opt,l,r,x;
	while(m--){
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1){
			scanf("%d",&x);
			modify_add(1,1,n,l,r,x);
		}
		else if(opt==2){
			scanf("%d",&x);
			modify_max(1,1,n,l,r,x);
		}
		else if(opt==3){
			scanf("%d",&x);
			modify_min(1,1,n,l,r,x);
		}
		else if(opt==4)
			printf("%lld\n",query_sum(1,1,n,l,r));
		else if(opt==5)
			printf("%d\n",query_max(1,1,n,l,r));
		else
			printf("%d\n",query_min(1,1,n,l,r));
	}
	return 0;
}
