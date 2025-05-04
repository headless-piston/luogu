#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=5e5+10,M=2e6+10;
int n,m;
struct edge{
	int to,nxt;
	bool bridge;
}e[M*2];
int head[N],tot=1;
void add_edge(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
int dfn[N],dfn_cnt,low[N];
void tarjan(int u,int fa){
	dfn[u]=low[u]=++dfn_cnt;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				e[i].bridge=1;
				e[i^1].bridge=1;
			}
		}
		else if(v!=fa)
			low[u]=min(low[u],dfn[v]);
	}
	return;
}
bool vis[N];
int dcc_cnt;
vector<int> dcc[N];
void dfs(int u){
	vis[u]=1;
	dcc[dcc_cnt].push_back(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!e[i].bridge&&!vis[v])
			dfs(v);
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i,0);
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			dcc_cnt++;
			dfs(i);
		}
	printf("%d\n",dcc_cnt);
	for(int i=1;i<=dcc_cnt;i++){
		printf("%d ",(int)dcc[i].size());
		for(int x:dcc[i])
			printf("%d ",x);
		printf("\n");
	}
	return 0;
}
