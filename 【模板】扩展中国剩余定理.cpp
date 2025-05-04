#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
long long a[N],m[N],n;
long long exgcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	long long d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
long long exCRT(){
	long long a1=a[1],m1=m[1];
	for(int i=2;i<=n;i++){
		long long a2=a[i],m2=m[i];
		long long xi,yi;
		long long g=exgcd(m1,m2,xi,yi);
		if((a2-a1)%g!=0)
			return -1;//无解
		long long lcm=(__int128)m1*m2/g;
		long long diff=(a2-a1)/g;
		a1=a1+(__int128)xi*diff%(m2/g)*m1;
		m1=lcm;
	}
	return (a1+m1)%m1;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",m+i,a+i);
	printf("%lld",exCRT());
	return 0;
}
