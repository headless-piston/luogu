#include<cstdio>
#include<stack>
#include<algorithm>
using namespace std;
const int N=2e6+10;//每个bool变量表示为两个点
int n,m;
struct edge{
	int to,nxt;
}e[N];//每个条件转换为两条边
int head[N],tot;
void add_edge(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
int dfn[N],low[N],dfn_cnt,scc_cnt,scc[N];
stack<int> st;
bool instack[N];
void tarjan(int u){
	dfn[u]=low[u]=++dfn_cnt;
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
		scc_cnt++;
		while(1){
			int v=st.top();
			st.pop();
			instack[v]=0;
			scc[v]=scc_cnt;
			if(v==u)
				break;
		}
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x1,x2,a,b;
		scanf("%d%d%d%d",&x1,&a,&x2,&b);
		int u=a?x1+n:x1;//x1+n表示¬x1
		int v=b?x2:x2+n;//x1非a->x2 b
		add_edge(u,v);
		u=b?x2+n:x2;
		v=a?x1:x1+n;//x2非b->x1 a
		add_edge(u,v);
	}
	for(int i=1;i<=n*2;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
		if(scc[i]==scc[i+n]){
			printf("IMPOSSIBLE");
			return 0;
		}
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++)//选用拓扑序较大的为真
		printf("%d ",scc[i]<scc[i+n]?1:0);//scc是逆拓扑序
	return 0;
}
