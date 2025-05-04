#include<iostream>
#include<queue>
using namespace std;
const int N=1e6+10;
int n,son[N][30],fail[N],e[N],tot;
void insert(string s){
	int len=s.size(),u=0;
	for(int i=0;i<len;i++){
		if(!son[u][s[i]-'a'])
			son[u][s[i]-'a']=++tot;
		u=son[u][s[i]-'a'];
	}
	e[u]++;
	return;
}
queue<int> q;
void get_fail(){
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
int query(string s){
	int len=s.size();
	int u=0,res=0;
	for(int i=0;i<len;i++){
		u=son[u][s[i]-'a'];
		for(int j=u;j&&e[j]!=-1;j=fail[j]){
			res+=e[j];
			e[j]=-1;
		}
	}
	return res;
}
string s,t;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(s);
	}
	cin>>t;
	get_fail();
	cout<<query(t);
	return 0;
}
