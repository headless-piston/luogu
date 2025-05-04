#include<iostream>
#include<queue>
using namespace std;
const int N=2e5+10;
int n,ans[N],tot,son[N][26],fail[N];
int pos[N];//每个模式串的结束节点
int ord[N],tot1;//拓扑排序节点顺序
int cnt[N];//每个节点的出现次数
void insert(string s,int id){
	int len=s.size(),u=0;
	for(int i=0;i<len;i++){
		if(!son[u][s[i]-'a'])
			son[u][s[i]-'a']=++tot;
		u=son[u][s[i]-'a'];
	}
	pos[id]=u;
	return;
}
queue<int> q;
void get_fail(){
	for(int i=0;i<26;i++)
		if(son[0][i]){
			q.push(son[0][i]);
			ord[++tot1]=son[0][i];
		}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(son[u][i]){
				fail[son[u][i]]=son[fail[u]][i];
				q.push(son[u][i]);
				ord[++tot1]=son[u][i];
			}
			else
				son[u][i]=son[fail[u]][i];
		}
	}
	return;
}
void topo(){
	for(int i=tot1;i;i--){
		int u=ord[i];
		cnt[fail[u]]+=cnt[u];
	}
	for(int i=1;i<=n;i++)
		ans[i]=cnt[pos[i]];
	return;
}
void query(string s){
	int u=0,len=s.size();
	for(int i=0;i<len;i++){
		u=son[u][s[i]-'a'];
		cnt[u]++;
	}
	topo();
	return;
}
string t[N],s;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		insert(t[i],i);
	}
	get_fail();
	cin>>s;
	query(s);
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
