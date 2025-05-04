#include<cstdio>
#include<cstring>
#define mod 19260817
const int N=10005;
char num[N];
long long read(){
	long long ans=0;
	memset(num,0,sizeof(num));
	scanf("%s",num);
	for(int i=0;i<strlen(num);i++)
		ans=(ans*10+num[i]-'0')%mod;
	return ans;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	long long d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
long long a,b,xi,yi;
int main(){
	a=read(),b=read();
	exgcd(b,mod,xi,yi);
	xi=(xi+mod)%mod;
	printf("%lld",(xi*a)%mod);
	return 0;
}
