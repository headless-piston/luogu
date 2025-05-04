#include<cstdio>
const int N=1e5+10;
int n,m,p1,fa[N],root[N],tot,q,p[N];
int find(int x){
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
struct segtree{
	int sum,ls,rs;
}tree[N*50];
void push_up(int u){
	tree[u].sum=tree[tree[u].ls].sum+tree[tree[u].rs].sum;
	return;
}
void modify(int &u,int l,int r,int x){
	if(!u)
		u=++tot;
	if(l==r){
		tree[u].sum++;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
		modify(tree[u].ls,l,mid,x);
	else
		modify(tree[u].rs,mid+1,r,x);
	push_up(u);
	return;
}
int unify(int u1,int u2,int l,int r){
	if(!u1)
		return u2;
	if(!u2)
		return u1;
	if(l==r){
		tree[u1].sum+=tree[u2].sum;
		return u1;
	}
	int mid=(l+r)/2;
	tree[u1].ls=unify(tree[u1].ls,tree[u2].ls,l,mid);
	tree[u1].rs=unify(tree[u1].rs,tree[u2].rs,mid+1,r);
	push_up(u1);
	return u1;
}
int query(int u,int k,int l,int r){
	if(tree[u].sum<k)
		return -1;
	if(l==r)
		return p[l];
	int mid=(l+r)/2;
	if(tree[tree[u].ls].sum>=k)
		return query(tree[u].ls,k,l,mid);
	else
		return query(tree[u].rs,k-tree[tree[u].ls].sum,mid+1,r);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++){
		scanf("%d",&p1);
		modify(root[i],1,n,p1);
		p[p1]=i;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		int a=find(u),b=find(v);
		if(a==b)
			continue;
		fa[b]=a;
		root[a]=unify(root[a],root[b],1,n);
	}
	scanf("%d",&q);
	while(q--){
		char op;
		int x,y;
		scanf(" %c %d%d",&op,&x,&y);
		if(op=='Q')
			printf("%d\n",query(root[find(x)],y,1,n));
		else{
			int a=find(x),b=find(y);
			if(a==b)
				continue;
			fa[b]=a;
			root[a]=unify(root[a],root[b],1,n);
		}
	}
	return 0;
}
