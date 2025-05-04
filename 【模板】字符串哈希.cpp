#include<iostream>
#include<algorithm>
#define mod1 1000000009
#define mod2 998244353
using namespace std;
const int N=1000010;
int n,ans=1,base1,base2;
string s;
pair<int,int> hash_num[N];
pair<int,int> Hash(string s){
	int hash1=0,hash2=0;
	base1=base2=1;
	for(int i=0;i<(int)s.length();i++){
		hash1=(hash1+1ll*s[i]*base1)%mod1;
		hash2=(hash2+1ll*s[i]*base2)%mod2;
		base1=1ll*base1*101%mod1;
		base2=1ll*base2*131%mod2;
	}
	return make_pair(hash1,hash2);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		hash_num[i]=Hash(s);
	}
	sort(hash_num+1,hash_num+1+n);
	for(int i=1;i<n;i++){
		if(hash_num[i]!=hash_num[i+1])
			ans++;
	}
	cout<<ans;
	return 0;
}
