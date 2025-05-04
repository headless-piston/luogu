#include<iostream>
#include<vector>
#include<unordered_map>
#include<stack>
using namespace std;
const int N=8010;
int n,tot,m;
unordered_map<string,int> mp;
vector<int> e[N];
void add_edge(int u,int v){
	e[u].push_back(v);
	return;
}
stack<int> st;
bool vis[N];
int dfn[N],low[N],scctot,scc[N],dfncnt;
void tarjan(int u){
	dfn[u]=low[u]=++dfncnt;
	st.push(u);
	vis[u]=1;
	for(int v:e[u])
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[v],low[u]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){
		scctot++;
		vis[u]=0;
		while(1){
			int v=st.top();
			st.pop();
			scc[v]=scctot;
			vis[v]=0;
			if(v==u)
				break;
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		string a,b;
		cin>>a>>b;
		mp[a]=++tot,mp[b]=++tot;
		add_edge(mp[a],mp[b]);
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		string a,b;
		cin>>a>>b;
		add_edge(mp[b],mp[a]);
	}
	for(int i=1;i<=2*n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<2*n;i+=2)
		if(scc[i]==scc[i+1])
			cout<<"Unsafe\n";
		else
			cout<<"Safe\n";
	return 0;
}
