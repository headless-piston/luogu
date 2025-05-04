#include<cstdio>
#include<algorithm>
const int N=1e5+10;
int n,m,head[N],edge_cnt,root[N],tot;
int dep[N],f[N][25],ans[N];
struct edge{
	int to,nxt;
}e[N*2];
void add_edge(int u,int v){
	e[++edge_cnt].to=v;
	e[edge_cnt].nxt=head[u];
	head[u]=edge_cnt;
	return;
}
struct segtree{
	int maxn,max_id,ls,rs;
}tree[N*50];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	for(int i=1;i<=20;i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)
			dfs(v,u);
	}
	return;
}
int lca(int x,int y){
	if(dep[x]>dep[y])
		std::swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[y]-(1<<i)>=dep[x])
			y=f[y][i];
	if(x==y)
		return x;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=0&&f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void push_up(int u){
	int maxl=tree[tree[u].ls].maxn,maxr=tree[tree[u].rs].maxn;
	int lid=tree[tree[u].ls].max_id,rid=tree[tree[u].rs].max_id;
	if(maxl>maxr){
		tree[u].maxn=maxl;
		tree[u].max_id=lid;
	}
	else if(maxl<maxr){
		tree[u].maxn=maxr;
		tree[u].max_id=rid;
	}
	else{
		tree[u].maxn=maxl;
		if(!lid)
			tree[u].max_id=rid;
		else if(!rid)
			tree[u].max_id=lid;
		else
			tree[u].max_id=std::min(lid,rid);
	}
	return;
}
void modify(int &u,int l,int r,int x,int k){
	if(!u)
		u=++tot;
	if(l==r){
		tree[u].maxn+=k;
		tree[u].max_id=x;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
		modify(tree[u].ls,l,mid,x,k);
	else
		modify(tree[u].rs,mid+1,r,x,k);
	push_up(u);
	return;
}
int unify(int u1,int u2,int l,int r){
	if(!u1)
		return u2;
	if(!u2)
		return u1;
	if(l==r){
		tree[u1].maxn+=tree[u2].maxn;
		tree[u1].max_id=l;
		return u1;
	}
	int mid=(l+r)/2;
	tree[u1].ls=unify(tree[u1].ls,tree[u2].ls,l,mid);
	tree[u1].rs=unify(tree[u1].rs,tree[u2].rs,mid+1,r);
	push_up(u1);
	return u1;
}
void dfs_unify(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs_unify(v,u);
			root[u]=unify(root[u],root[v],1,1e5);
		}
	}
	ans[u]=tree[root[u]].maxn?tree[root[u]].max_id:0;
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		int k=lca(x,y);
		modify(root[x],1,1e5,z,1);
		modify(root[y],1,1e5,z,1);
		modify(root[k],1,1e5,z,-1);
		if(f[k][0])
			modify(root[f[k][0]],1,1e5,z,-1);
	}
	dfs_unify(1,0);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
