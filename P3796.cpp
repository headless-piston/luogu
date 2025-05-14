#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int N=150*70+10;
int n,tot,son[N][30],e[N],fail[N],maxn,ans[200];
void insert(string s,int id){
	int len=s.size(),u=0;
	for(int i=0;i<len;i++){
		if(!son[u][s[i]-'a'])
			son[u][s[i]-'a']=++tot;
		u=son[u][s[i]-'a'];
	}
	e[u]=id;
	return;
}
void get_fail(){
	queue<int> q;
	for(int i=0;i<26;i++)
		if(son[0][i]){
			fail[son[0][i]]=0;
			q.push(son[0][i]);
		}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(son[u][i]){
				fail[son[u][i]]=son[fail[u]][i];
				q.push(son[u][i]);
			}
			else
				son[u][i]=son[fail[u]][i];
		}
	}
	return;
}
void query(string s){
	int u=0,len=s.size();
	for(int i=0;i<len;i++){
		u=son[u][s[i]-'a'];
		for(int j=u;j;j=fail[j]){
			if(e[j]){	
				ans[e[j]]++;
				maxn=max(maxn,ans[e[j]]);
			}
		}
	}
	return;
}
string s[200],t;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	while(cin>>n&&n){
		memset(son,0,sizeof(son));
		memset(e,0,sizeof(e));
		memset(ans,0,sizeof(ans));
		memset(fail,0,sizeof(fail));
		maxn=tot=0;
		for(int i=1;i<=n;i++){
			cin>>s[i];
			insert(s[i],i);
		}
		get_fail();
		cin>>t;
		query(t);
		cout<<maxn<<'\n';
		for(int i=1;i<=n;i++)
			if(ans[i]==maxn)
				cout<<s[i]<<'\n';
	}
	return 0;
}
