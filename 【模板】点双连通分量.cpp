#include<cstdio>
#include<stack>
#include<vector>
using namespace std;
const int N=5e5+10,M=2e6+10;
int n,m;
struct edge{
	int to,nxt;
}e[M*2];
int head[N],tot;
void add_edge(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
int low[N],dfn[N],dfn_cnt,bcc_cnt,root;
vector<int> bcc[N];
stack<int> st;
void tarjan(int u){
	low[u]=dfn[u]=++dfn_cnt;
	st.push(u);
	if(u==root&&!head[u]){
		bcc[++bcc_cnt].push_back(u);
		return;
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				bcc[++bcc_cnt].push_back(u);
				while(1){
					int x=st.top();
					st.pop();
					bcc[bcc_cnt].push_back(x);
					if(x==v)
						break;
				}
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(u==v)
			continue;
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			root=i,tarjan(i);
	printf("%d\n",bcc_cnt);
	for(int i=1;i<=bcc_cnt;i++){
		printf("%d ",(int)bcc[i].size());
		for(int x:bcc[i])
			printf("%d ",x);
		printf("\n");
	}
	return 0;
}
