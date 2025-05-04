#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e4+10,M=1e8+10;
int n,m,head[N],tot;
struct edge{
	int to,nxt,w;
}e[2*N];
void add(int u,int v,int w){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].w=w;
	head[u]=tot;
	return;
}
int root,max_son[N],siz[N],dis[N],rem[N],sum,cnt;
int query[110],q[N];
bool vis[N],ok[M],res[110];
void get_root(int u,int fa){
	siz[u]=1,max_son[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa||vis[v])
			continue;
		get_root(v,u);
		siz[u]+=siz[v];
		max_son[u]=max(max_son[u],siz[v]);
	}
	max_son[u]=max(max_son[u],sum-siz[u]);
	if(max_son[u]<max_son[root])
		root=u;
	return;
}
void get_dis(int u,int fa){
	rem[++cnt]=dis[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa||vis[v])
			continue;
		dis[v]=dis[u]+e[i].w;
		get_dis(v,u);
	}
	return;
}
void calc(int u){
	int p=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])
			continue;
		cnt=0;
		dis[v]=e[i].w;
		get_dis(v,u);
		for(int j=0;j<=cnt;j++)
			for(int k=1;k<=m;k++)
				if(query[k]>=rem[j])
					res[k]|=ok[query[k]-rem[j]];
		for(int j=0;j<=cnt;j++)
			q[++p]=rem[j],ok[rem[j]]=1;
	}
	for(int i=1;i<=p;i++)
		ok[q[i]]=0;
	return;
}
void solve(int u){
	vis[u]=ok[0]=1;
	calc(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])
			continue;
		sum=siz[v];
		root=0;
		max_son[root]=1e9;
		get_root(v,0);
		solve(root);
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=m;i++)
		scanf("%d",&query[i]);
	sum=max_son[root]=n;
	get_root(1,0);
	solve(root);
	for(int i=1;i<=m;i++)
		if(res[i])
			printf("AYE\n");
		else
			printf("NAY\n");
	return 0;
}
