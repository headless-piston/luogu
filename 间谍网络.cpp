#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3010;
int n,p,r,tot,tot1,head[N],dfn[N],low[N],cnt,ans,minn[N],color[N],sum[N],indegree[N],x[N*N],y[N*N],w[N];
bool instack[N],flag;
struct edge{
	int to,nxt;
}e[N*N];
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
	if(dfn[u]==low[u]){
		instack[u]=0;
		tot1++;
		while(1){
			int v=st.top();
			st.pop();
			color[v]=tot1;
			sum[tot1]=min(sum[tot1],w[v]);
			instack[v]=0;
			if(u==v)
				break;
		}
	}
	return;
}
bool vis[N];
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			vis[v]=1;
			dfs(v);
		}
	}
	return;
}
int main(){
	memset(w,0x3f,sizeof(w));
	memset(minn,0x3f,sizeof(minn));
	memset(sum,0x3f,sizeof(sum));
	scanf("%d%d",&n,&p);
	for(int i=1;i<=p;i++){
		int a;
		scanf("%d",&a);
		scanf("%d",&w[a]);
	}
	scanf("%d",&r);
	for(int i=1;i<=r;i++){
		scanf("%d%d",&x[i],&y[i]);
		add(x[i],y[i]);
	}
	for(int i=1;i<=n;i++)
		if(w[i]!=0x3f3f3f3f)
			dfs(i),vis[i]=1;
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			printf("NO\n%d",i);
			return 0;
		}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	tot=0;
	memset(e,0,sizeof(e));
	memset(head,0,sizeof(head));
	for(int i=1;i<=r;i++){
		int u=color[x[i]],v=color[y[i]];
		if(u!=v){
			indegree[v]++;
			add(u,v);
		}
	}
	for(int i=1;i<=tot1;i++)
		if(indegree[i]==0)
			ans+=sum[i];
	printf("YES\n");
	printf("%d",ans);
	return 0;
}
