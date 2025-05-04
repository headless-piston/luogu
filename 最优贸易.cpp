#include<cstdio>
#include<queue>
#include<algorithm>
#include<stack>
#include<cstring>
using namespace std;
const int N=100010,M=500010;
int n,m,tot,tot1,tot2,head[N],dfn[N],low[N],cnt;
int vis[N],ans,color[N],maxn[N],minn[N],indegree[N],w[N],x[M],y[M],z;
struct edge{
	int to,nxt;
}e[M*2],e1[M*2];
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
stack<int> st;
void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	st.push(u);
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[v],low[u]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		vis[u]=0;
		tot1++;
		while(1){
			int v=st.top();
			st.pop();
			color[v]=tot1;
			maxn[tot1]=max(maxn[tot1],w[v]);
			minn[tot1]=min(minn[tot1],w[v]);
			vis[v]=0;
			if(u==v)
				break;
		}
	}
	return;
}
queue<int> q;
int dp[N],list[N];
void topo(){
	q.push(color[1]);
	while(q.size()){
		int u=q.front();
		q.pop();
		list[++tot2]=u;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(--indegree[v]==0)
				q.push(v);
		}
	}
	return;
}
bool vis1[N];
int head1[N],tot11;
void add1(int u,int v){
	e1[++tot11].to=v;
	e1[tot11].nxt=head1[u];
	head1[u]=tot11;
	return;
}
void dfs(int u){
	for(int i=head1[u];i;i=e1[i].nxt){
		int v=e1[i].to;
		if(!vis1[v]){
			vis1[v]=1;
			dfs(v);
		}
	}
	return;
}
int main(){
	memset(minn,0x3f,sizeof(minn));
	memset(maxn,-1,sizeof(maxn));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x[i],&y[i],&z);
		add(x[i],y[i]);
		if(z==2)
			add(y[i],x[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	memset(head,0,sizeof(head));
	memset(e,0,sizeof(e));
	tot=0;
	for(int i=1;i<=m;i++){
		int u=color[x[i]],v=color[y[i]];
		if(u!=v){
			indegree[v]++;
			add(u,v);
			add1(v,u);
		}
	}
	topo();
	vis1[color[n]]=1;
	dfs(color[n]);
	for(int i=1;i<=tot1;i++)
		dp[i]=minn[i];
	for(int i=1;i<=tot1;i++){
		int u=list[i];
		if(vis1[u])
			ans=max(ans,maxn[u]-dp[u]);
		for(int j=head[u];j;j=e[j].nxt){
			int v=e[j].to;
			dp[v]=min(dp[v],dp[u]);
		}
	}
	printf("%d",ans);
	return 0;
}
