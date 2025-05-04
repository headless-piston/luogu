#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+10;
string opt;
int tree[N*4],cnt,tot,head[N],tag[N*4],n,dfn[N],son[N],top[N],siz[N],fa[N],dep[N],q;
struct edge{
	int to,nxt;
}e[N*2];
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
void push_up(int u){
	tree[u]=tree[u*2]+tree[u*2+1];
	return;
}
void push_down(int u,int l,int r){
	if(tag[u]==-1)
		return;
	int mid=(l+r)/2;
	tree[u*2]=tag[u]*(mid-l+1);
	tree[u*2+1]=tag[u]*(r-mid);
	tag[u*2]=tag[u*2+1]=tag[u];
	tag[u]=-1;
	return;
}
void modify(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]=k*(r-l+1);
		tag[u]=k;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	modify(u*2,l,mid,x,y,k);
	modify(u*2+1,mid+1,r,x,y,k);
	push_up(u);
	return;
}
int query(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return 0;
	if(x<=l&&y>=r)
		return tree[u];
	push_down(u,l,r);
	int mid=(l+r)/2;
	return query(u*2,l,mid,x,y)+query(u*2+1,mid+1,r,x,y);
}
void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	siz[u]=1;
	fa[u]=f;
	int maxson=-1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=f){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>maxson){
				son[u]=v;
				maxson=siz[v];
			}
		}
	}
	return;
}
void dfs2(int u,int topf){
	dfn[u]=++cnt;
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa[u]&&v!=son[u])
			dfs2(v,v);
	}
	return;
}
int tree_sum(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans+=query(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ans+=query(1,1,n,dfn[x],dfn[y]);
	return ans;
}
void tree_add(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		modify(1,1,n,dfn[top[x]],dfn[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	modify(1,1,n,dfn[x],dfn[y],k);
	return;
}
void install(int x){
	int ans1=tree_sum(1,x);
	tree_add(1,x,1);
	int ans2=tree_sum(1,x);
	printf("%d\n",ans2-ans1);
	return;
}
void uninstall(int x){
	printf("%d\n",query(1,1,n,dfn[x],dfn[x]+siz[x]-1));
	modify(1,1,n,dfn[x],dfn[x]+siz[x]-1,0);
	return;
}
int main(){
	memset(tag,-1,sizeof(tag));
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int x;
		scanf("%d",&x);
		x++;
		add(i,x);
		add(x,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	scanf("%d",&q);
	while(q--){
		cin>>opt;
		int x;
		scanf("%d",&x);
		x++;
		if(opt=="install")
			install(x);
		else
			uninstall(x);
	}
	return 0;
}
