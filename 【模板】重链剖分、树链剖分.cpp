#include<cstdio>
#include<algorithm>
const int N=1e5+10;
int tree[N*4],tag[N*4],opt,w[N],dep[N],fa[N],siz[N],n,m,r,p,son[N];
int head[N],tot,dfn[N],cnt,top[N],w1[N];
struct edge{
	int to,nxt;
}e[N*2];
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
void build(int u,int l,int r){
	if(l==r){
		tree[u]=w1[l]%p;//根据新权值建树 
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	tree[u]=(tree[u*2]+tree[u*2+1])%p;
	return;
}
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	tree[u*2]=(tree[u*2]+tag[u]*(mid-l+1))%p;
	tree[u*2+1]=(tree[u*2+1]+tag[u]*(r-mid))%p;
	tag[u*2]=(tag[u*2]+tag[u])%p;
	tag[u*2+1]=(tag[u*2+1]+tag[u])%p;
	tag[u]=0;
	return;
}
void modify(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]=(tree[u]+k*(r-l+1))%p;
		tag[u]=(tag[u]+k)%p;
		return;
	}
	int mid=(l+r)/2;
	push_down(u,l,r);
	modify(u*2,l,mid,x,y,k);
	modify(u*2+1,mid+1,r,x,y,k);
	tree[u]=(tree[u*2]+tree[u*2+1])%p;
	return;
}
int query(int u,int l,int r,int x,int y){
	if(x>r||y<l)
		return 0;
	if(x<=l&&y>=r)
		return tree[u]%p;
	int mid=(l+r)/2;
	push_down(u,l,r);
	return (query(u*2,l,mid,x,y)+query(u*2+1,mid+1,r,x,y))%p;
}
void dfs1(int u,int f){
	dep[u]=dep[f]+1;//深度 
	siz[u]=1;//子树大小 
	fa[u]=f;//父节点 
	int maxson=-1;//子节点中最大的siz，也就是重儿子所对的siz 
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=f){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>maxson){
				son[u]=v;//重儿子 
				maxson=siz[v];
			}
		}
	}
	return;
}
void dfs2(int u,int topf){
	dfn[u]=++cnt;//dfn序，也就是线段树上的编号 
	top[u]=topf;//当前树链的最顶端节点 
	w1[cnt]=w[u];//新的权值 
	if(!son[u])
		return;
	dfs2(son[u],topf);//重儿子的处理 
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa[u]&&v!=son[u])//轻儿子的处理 
			dfs2(v,v);
	}
	return;
}
int tree_sum(int x,int y){//x到y路径上的和 
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			std::swap(x,y);
		ans=(ans+query(1,1,n,dfn[top[x]],dfn[x]))%p;
		x=fa[top[x]];//跳到链顶的父节点 
	}
	if(dep[x]>dep[y])
		std::swap(x,y);
	ans=(ans+query(1,1,n,dfn[x],dfn[y]))%p;
	return ans;
}
void tree_add(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			std::swap(x,y);
		modify(1,1,n,dfn[top[x]],dfn[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		std::swap(x,y);
	modify(1,1,n,dfn[x],dfn[y],k);
	return;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&r,&p);
	for(int i=1;i<=n;i++)
		scanf("%d",w+i);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs1(r,0);
	dfs2(r,r);
	build(1,1,n);
	while(m--){
		int x,y,z;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d%d",&x,&y,&z);
			tree_add(x,y,z%p);
		}
		else if(opt==2){
			scanf("%d%d",&x,&y);
			printf("%d\n",tree_sum(x,y));
		}
		else if(opt==3){
			scanf("%d%d",&x,&z);
			modify(1,1,n,dfn[x],dfn[x]+siz[x]-1,z%p);
		}
		else{
			scanf("%d",&x);
			printf("%d\n",query(1,1,n,dfn[x],dfn[x]+siz[x]-1));
		}
	}
	return 0;
}
