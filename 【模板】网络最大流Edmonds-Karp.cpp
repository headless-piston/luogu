#include<cstdio>
#include<queue>
#include<cstring>
#define inf 1e18
using namespace std;
const int N=210,M=5010;
int head[N],tot=1,n,m,s,t;
int pre[N];//路径的前驱节点
long long flow[N];//各边剩余容量最小值
struct edge{
	int to,nxt;
	long long c;//剩余容量
}e[M*2];
int flag[N][N];
long long ans;
void add_edge(int u,int v,long long c){
	e[++tot].to=v;
	e[tot].c=c;
	e[tot].nxt=head[u];
	head[u]=tot;//正向边
	e[++tot].to=u;
	e[tot].c=0;
	e[tot].nxt=head[v];
	head[v]=tot;//反向边
	return;
}
bool bfs(){
	memset(pre,0,sizeof(pre));
	queue<int> q;
	q.push(s);
	pre[s]=s;
	flow[s]=inf;
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].c==0||pre[v])
				continue;
			flow[v]=min(flow[u],e[i].c);
			pre[v]=i;
			q.push(v);
			if(v==t)
				return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		int u,v;
		long long w;
		scanf("%d%d%lld",&u,&v,&w);
		if(!flag[u][v]){
			add_edge(u,v,w);
			flag[u][v]=tot;
		}
		else
			e[flag[u][v]^1].c+=w;
	}
	while(bfs()){
		for(int u=t;u!=s;u=e[pre[u]^1].to){
			e[pre[u]].c-=flow[t];
			e[pre[u]^1].c+=flow[t];
		}
		ans+=flow[t];
	}
	printf("%lld",ans);
	return 0;
}
