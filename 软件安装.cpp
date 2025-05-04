#include<iostream>
#include<vector>
#include<stack>
using namespace std;
const int N=110;
int n,m,w[N],val[N];
vector<int> e[N],e1[N];
void add_edge(int u,int v){
	e[u].push_back(v);
	return;
}
void add_edge1(int u,int v){
	e1[u].push_back(v);
	return;
}
int dfn[N],low[N],dfncnt,scccnt,scc[N],w1[N],val1[N];
bool instack[N];
stack<int> st;
void tarjan(int u){
	dfn[u]=low[u]=++dfncnt;
	instack[u]=1;
	st.push(u);
	for(int v:e[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		scccnt++;
		while(1){
			int v=st.top();
			st.pop();
			instack[v]=0;
			scc[v]=scccnt;
			w1[scccnt]+=w[v];
			val1[scccnt]+=val[v];
			if(u==v)
				break;
		}
	}
	return;
}
int dp[N][N*5],indeg[N];
void dfs(int u){
	for(int i=w1[u];i<=m;i++)
		dp[u][i]=val1[u];
	for(int v:e1[u]){
		dfs(v);
		for(int i=m;i>=0;i--)
			for(int j=0;j<=i-w1[u];j++)
				dp[u][i]=max(dp[u][i],dp[u][i-j]+dp[v][j]);
	}
	return;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	for(int i=1;i<=n;i++)
		cin>>val[i];
	for(int v=1,u;v<=n;v++){
		cin>>u;
		add_edge(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int u=1;u<=n;u++)
		for(int v:e[u])
			if(scc[u]!=scc[v])
				add_edge1(scc[u],scc[v]),indeg[scc[v]]++;
	for(int i=1;i<=scccnt;i++)
		if(!indeg[i])
			add_edge1(0,i);
	dfs(0);
	cout<<dp[0][m];
	return 0;
}
