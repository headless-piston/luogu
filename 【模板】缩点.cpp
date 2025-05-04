#include<cstdio>
#include<stack>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e4+10,M=2e5+10;
int n,m,w[N],head[N],tot1,tot,low[N],dfn[N],cnt,color[N],dis[N],ans,w1[N],x[M],y[M],indegree[N];
struct edge{
	int to,nxt;
}e[M];
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
bool vis[N],instack[N];
stack<int> st;
void tarjan(int u){
	low[u]=dfn[u]=++cnt;
	st.push(u);
	instack[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(instack[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		tot1++;
		instack[u]=0;
		while(1){
			int v=st.top();
			st.pop();
			color[v]=tot1;
			w1[tot1]+=w[v];
			instack[v]=0;
			if(v==u)
				break;
		}
	}
	return;
}
queue<int> q;
int dp[N];
void topo(){
	for(int i=1;i<=tot1;i++)
		if(indegree[i]==0){
			q.push(i);
			dp[i]=w1[i];
		}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			dp[v]=max(dp[v],dp[u]+w1[v]);
			if(--indegree[v]==0)
				q.push(v);
		}
	}
	for(int i=1;i<=tot1;i++)
		ans=max(ans,dp[i]);
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x[i],&y[i]);
		add(x[i],y[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	memset(e,0,sizeof(e));
	memset(head,0,sizeof(head));
	tot=0;
	for(int i=1;i<=m;i++)
		if(color[x[i]]!=color[y[i]]){
			indegree[color[y[i]]]++;
			add(color[x[i]],color[y[i]]);
		}
	topo();
	printf("%d",ans);
	return 0;
}
