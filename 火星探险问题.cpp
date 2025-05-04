#include<iostream>
#include<queue>
#include<cstring>
#define inf 2e9
using namespace std;
const int N=35*35*2+10,M=1e5+10;
int p,q,nodecnt,node[N][N],tot=1,head[N],n;
struct edge{
	int to,nxt,c,w;
}e[M];
void add_edge1(int u,int v,int c,int w){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].c=c;
	e[tot].w=w;
	head[u]=tot;
	return;
}
void add_edge(int u,int v,int c,int w){
	add_edge1(u,v,c,w);
	add_edge1(v,u,0,-w);
	return;
}
int pre[N],dis[N],s,t,flow[N];
bool vis[N];
queue<int> que;
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(flow,0,sizeof(flow));
	dis[s]=0;
	vis[s]=1;
	flow[s]=inf;
	que.push(s);
	while(!que.empty()){
		int u=que.front();
		que.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,c=e[i].c,w=e[i].w;
			if(c&&dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				pre[v]=i;
				flow[v]=min(flow[u],c);
				if(!vis[v]){
					vis[v]=1;
					que.push(v);
				}
			}
		}
	}
	return flow[t]>0;
}
int cnt[N][N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>p>>q;
	for(int i=1;i<=q;i++)
		for(int j=1;j<=p;j++)
			node[i][j]=++nodecnt;
	for(int i=1,c;i<=q;i++){
		for(int j=1;j<=p;j++){
			cin>>c;
			if(c==1)
				continue;
			add_edge(node[i][j],node[i][j]+nodecnt,inf,0);
			if(c==2)
				add_edge(node[i][j],node[i][j]+nodecnt,1,-1);
			if(i<q)
				add_edge(node[i][j]+nodecnt,node[i+1][j],inf,0);
			if(j<p)
				add_edge(node[i][j]+nodecnt,node[i][j+1],inf,0);
		}
	}
	s=0,t=nodecnt*2+1;
	add_edge(s,node[1][1],n,0);
	add_edge(node[q][p]+nodecnt,t,n,0);
	while(spfa()){
		int minf=flow[t];
		for(int i=t,cnt=0;i!=s;i=e[pre[i]^1].to,cnt++){
			e[pre[i]].c-=minf;
			e[pre[i]^1].c+=minf;
		}
	}
	for(int i=1;i<=q;i++)
		for(int j=1;j<=p;j++)
			for(int k=head[node[i][j]];k;k=e[k].nxt){
				int v=e[k].to;
				if(v==node[i][j]+nodecnt)
					cnt[i][j]+=e[k^1].c;
			}
	for(int i=1;i<=n;i++){
		int x=1,y=1;
		while(x!=q||y!=p){
			if(cnt[x+1][y]){
				cout<<i<<" 0\n";
				cnt[x+1][y]--;
				x++;
			}
			else{
				cout<<i<<" 1\n";
				cnt[x][y+1]--;
				y++;
			}
		}
	}
	return 0;
}
