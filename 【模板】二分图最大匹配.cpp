#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N=510;
int n,m,tot,ans;
vector<int> e[N];
int match[N];//右部点的匹配对象
bool vis[N];//右部点是否被访问
bool dfs(int u){
	for(int v:e[u]){
		if(!vis[v]){
			vis[v]=1;
			if(match[v]==0||dfs(match[v])){//dfs(match[v])表示为v的匹配对象换一个匹配对象
				match[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	scanf("%d%d%d",&n,&m,&tot);
	for(int i=1;i<=tot;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i))
			ans++;
	}
	printf("%d",ans);
	return 0;
}
