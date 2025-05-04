#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5050,M=2e5+10,MAX=0x7f7f7f7f;
int n,m,tot,head[N];
struct edge{
	int to,nxt,w;
}e[M*2];
void add(int u,int v,int w){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	e[tot].w=w;
	head[u]=tot;
	return;
}
int dis[N],cnt,p=1,ans;
bool vis[N];
void prim(){
	memset(dis,0x3f,sizeof(dis));
	for(int i=head[1];i;i=e[i].nxt)
		dis[e[i].to]=min(dis[e[i].to],e[i].w);
	while(++cnt<n){
		int minn=MAX;
		vis[p]=1;
		for(int i=1;i<=n;i++){
			if(!vis[i]&&minn>dis[i]){
				minn=dis[i];
				p=i;
			}
		}
		ans+=minn;
		for(int i=head[p];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>e[i].w&&!vis[v])
				dis[v]=e[i].w;
		}
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	prim();
	if(ans>0x3f3f3f3f)
		printf("orz");
	else
		printf("%d",ans);
	return 0;
}
