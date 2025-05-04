#include<cstdio>
#define int long long
using namespace std;
const int N=15;
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
int n,a[N],b[N],M=1,x;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&a[i],&b[i]);
	for(int i=1;i<=n;i++)
		M*=a[i];
	for(int i=1;i<=n;i++){
		int Mi=M/a[i];
		int xi,yi;
		exgcd(Mi,a[i],xi,yi);
		xi=(xi%a[i]+a[i])%a[i];
		x=(x+(__int128)b[i]*Mi%M*xi%M)%M;
	}
	printf("%lld",(x%M+M)%M);
	return 0;
}
