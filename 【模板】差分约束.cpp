#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=5e3+10,M=1e4+10;
int n,m,head[N],tot,cnt[N];
long long dis[N];
struct edge{
	int to,nxt,w;
}e[M];
void add(int u,int v,int w){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].w=w;
	head[u]=tot;
	return;
}
bool vis[N];
queue<int> q;
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	q.push(0);
	vis[0]=1;
	while(q.size()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				if(!vis[v]){
					q.push(v);
					vis[v]=1;
					cnt[v]++;
					if(cnt[v]==n+1)
						return 0;
				}
			}
		}
	}
	return 1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		add(0,i,0);//ÐéÄâÔ´µã 
	for(int i=1;i<=m;i++){
		int c1,c2,y;
		scanf("%d%d%d",&c1,&c2,&y);
		add(c2,c1,y);
	}
	if(spfa()){
		for(int i=1;i<=n;i++)
			printf("%d ",dis[i]);
		return 0;
	}
	printf("NO");
	return 0;
}
