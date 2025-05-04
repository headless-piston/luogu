#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=5e3+10,M=5e4+10;
struct edge{
	int to,nxt,c,w;
}e[M*2];
int tot=1,head[N],n,m,s,t;
void add_edge(int u,int v,int c,int w){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].c=c;
	e[tot].w=w;
	head[u]=tot;
	e[++tot].to=u;
	e[tot].nxt=head[v];
	e[tot].c=0;
	e[tot].w=-w;
	head[v]=tot;
	return;
}
int min_flow[N],dis[N],pre[N],flow,cost;
queue<int> q;
bool vis[N];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(min_flow,0,sizeof(min_flow));
	memset(vis,0,sizeof(vis));
	q.push(s);
	vis[s]=1;
	dis[s]=0;
	min_flow[s]=2e9;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,c=e[i].c,w=e[i].w;
			if(c&&dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				pre[v]=i;
				min_flow[v]=min(min_flow[u],c);
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return min_flow[t]>0;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int u,v,c,w;
		cin>>u>>v>>c>>w;
		add_edge(u,v,c,w);
	}
	while(spfa()){
		int minf=min_flow[t];
		for(int i=t;i!=s;i=e[pre[i]^1].to){
			e[pre[i]].c-=minf;
			e[pre[i]^1].c+=minf;
		}
		flow+=minf;
		cost+=minf*dis[t];
	}
	cout<<flow<<' '<<cost;
	return 0;
}
