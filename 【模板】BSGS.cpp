#include<cstdio>
#include<cmath>
#include<unordered_map>
using namespace std;
int qpow(int a,int b,int mod){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return res;
}
unordered_map<int,int> bs;
int p,b,n,t,x,y,inv,temp;
int main(){
	scanf("%d%d%d",&p,&b,&n);
	if(n==1){
		printf("0");
		return 0;
	}
	n%=p;
	b%=p;
	t=ceil(sqrt(p));
	x=1;
	for(int j=0;j<t;j++){
		if(!bs.count(x))
			bs[x]=j;
		x=1ll*x*b%p;
	}
	y=qpow(b,t,p);
	inv=qpow(y,p-2,p);
	temp=n;
	for(int i=0;i<t;i++){
		if(bs.count(temp)){
			int j=bs[temp];
			printf("%lld",1ll*i*t+j);
			return 0;
		}
		temp=1ll*temp*inv%p;
	}
	printf("no solution");
	return 0;
}
