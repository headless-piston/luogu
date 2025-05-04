#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
const ll N=20000000;
ll phi(ll n){
	ll ans=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans=ans/n*(n-1);
	return ans;
}
ll qpow(ll a,ll b,ll mod){
	a%=mod;
	ll res=1;
	while(b){
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll euler,a,m,b;
char s[N];
bool flag=1;
ll read(){
	ll res=0;
	scanf("%s",s);
	for(ll i=0;i<strlen(s);i++){
		res=res*10+s[i]-'0';
		if(res>euler){
			flag=0;
			res%=euler;
		}
	}
	return res;
}
int main(){
	scanf("%lld%lld",&a,&m);
	euler=phi(m);
	b=read();
	if(__gcd(a,m)==1){
		printf("%lld",qpow(a,b,m));
		return 0;
	}
	else if(flag){
		printf("%lld",qpow(a,b,m));
		return 0;
	}
	printf("%lld",qpow(a,b+euler,m));
	return 0;
}
