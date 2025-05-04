#include<cstdio>
const int N=2e5+10;
int n,m,root[N],tot,root_cnt;
struct segtree{
	long long sum;
	int ls,rs;
}tree[N*50];
void push_up(int u){
	tree[u].sum=tree[tree[u].ls].sum+tree[tree[u].rs].sum;
	return;
}
void modify(int &u,int l,int r,int x,int t){
	if(!u)
		u=++tot;
	if(l==r){
		tree[u].sum+=t;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
		modify(tree[u].ls,l,mid,x,t);
	else
		modify(tree[u].rs,mid+1,r,x,t);
	push_up(u);
	return;
}
void unify(int &u1,int u2,int l,int r){
	if(!u1){
		u1=u2;
		return;
	}
	if(!u2)
		return;
	if(l==r){
		tree[u1].sum+=tree[u2].sum;
		return;
	}
	int mid=(l+r)/2;
	unify(tree[u1].ls,tree[u2].ls,l,mid);
	unify(tree[u1].rs,tree[u2].rs,mid+1,r);
	push_up(u1);
	return;
}
void split(int &u1,int &u2,int l,int r,int x,int y){
	if(!u1)
		return;
	if(x<=l&&y>=r){
		u2=u1;
		u1=0;
		return;
	}
	if(!u2)
		u2=++tot;
	int mid=(l+r)/2;
	if(x<=mid)
		split(tree[u1].ls,tree[u2].ls,l,mid,x,y);
	if(y>mid)
		split(tree[u1].rs,tree[u2].rs,mid+1,r,x,y);
	push_up(u1);
	push_up(u2);
	return;
}
long long query_sum(int u,int l,int r,int x,int y){
	if(x<=l&&y>=r)
		return tree[u].sum;
	long long res=0;
	int mid=(l+r)/2;
	if(x<=mid)
		res+=query_sum(tree[u].ls,l,mid,x,y);
	if(y>mid)
		res+=query_sum(tree[u].rs,mid+1,r,x,y);
	return res;
}
long long query_kth(int u,int l,int r,int k){
	if(tree[u].sum<k)
		return -1;
	if(l==r)
		return l;
	int mid=(l+r)/2;
	if(tree[tree[u].ls].sum>=k)
		return query_kth(tree[u].ls,l,mid,k);
	else
		return query_kth(tree[u].rs,mid+1,r,k-tree[tree[u].ls].sum);
}
int main(){
	scanf("%d%d",&n,&m);
	root_cnt=1;
	for(int i=1;i<=n;i++){
		int val;
		scanf("%d",&val);
		modify(root[1],1,n,i,val);
	}
	while(m--){
		int opt;
		scanf("%d",&opt);
		if(opt==0){
			int p,x,y;
			scanf("%d%d%d",&p,&x,&y);
			split(root[p],root[++root_cnt],1,n,x,y);
		}
		else if(opt==1){
			int p,t;
			scanf("%d%d",&p,&t);
			unify(root[p],root[t],1,n);
			root[t]=0;
		}
		else if(opt==2){
			int p,x,q;
			scanf("%d%d%d",&p,&x,&q);
			modify(root[p],1,n,q,x);
		}
		else if(opt==3){
			int p,x,y;
			scanf("%d%d%d",&p,&x,&y);
			printf("%lld\n",query_sum(root[p],1,n,x,y));
		}
		else{
			int p,k;
			scanf("%d%d",&p,&k);
			printf("%lld\n",query_kth(root[p],1,n,k));
		}
	}
	return 0;
}
