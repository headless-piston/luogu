#include<cstdio>
#include<queue>
#include<cstring>
#define inf 1e18
using namespace std;
const int N=210,M=5010;
int n,m,s,t,tot=1,head[N];
long long ans;
struct edge{
	int to,nxt;
	long long c;
}e[M*2];
void add_edge(int u,int v,long long c){
	e[++tot].to=v;
	e[tot].c=c;
	e[tot].nxt=head[u];
	head[u]=tot;
	e[++tot].to=u;
	e[tot].c=0;
	e[tot].nxt=head[v];
	head[v]=tot;
	return;
}
int level[N];//层级
bool bfs(){
	memset(level,-1,sizeof(level));
	queue<int> q;
	q.push(s);
	level[s]=0;
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].c==0||level[v]!=-1)
				continue;
			level[v]=level[u]+1;
			q.push(v);
		}
	}
	return level[t]!=-1;
}
int cur[N];//当前弧优化
long long dfs(int u,long long flow){
	if(u==t)
		return flow;
	long long res=0;
	for(int i=cur[u];i;i=e[i].nxt){
		cur[u]=i;//当前弧优化
		int v=e[i].to;
		if(e[i].c==0||level[v]!=level[u]+1)//按层dfs
			continue;
		long long temp=dfs(v,min(flow-res,e[i].c));
		e[i].c-=temp;
		e[i^1].c+=temp;
		res+=temp;
		if(res==flow)
			break;
	}
	if(res==0)
		level[u]=-1;
	return res;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
	}
	while(bfs()){
		memcpy(cur,head,sizeof(head));//重置当前弧
		ans+=dfs(s,inf);
	}
	printf("%lld",ans);
	return 0;
}
