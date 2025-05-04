#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500010;
int n,m,s,head[N],tot,deep[N],f[N][21];
struct edge{
	int to,nxt;
}e[N<<1];
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
void dfs(int u,int pre){
	deep[u]=deep[pre]+1;
	f[u][0]=pre;
	for(int i=1;i<=20;i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=pre){
			f[v][0]=u;
			dfs(v,u);
		}
	}
	return;
}
int lca(int x,int y){
	if(deep[x]<deep[y])
		swap(x,y);
	for(int i=20;i>=0;i--){
		if(deep[f[x][i]]>=deep[y])
			x=f[x][i];
		if(x==y)
			return x;
	}
	for(int i=20;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
int main(){
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(s,0);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	return 0;
}
