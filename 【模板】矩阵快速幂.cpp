#include<cstdio>
#include<cstring>
#define mod 1000000007
#define int long long
int n,k;
struct matrix{
	int a[110][110];
	matrix(){
		memset(a,0,sizeof(a));
	}
	matrix operator*(const matrix &b)const{
		matrix res;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					res.a[i][j]=(res.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
		return res;
	}
}ans,base;
void qpow(int b){
	while(b>0){
		if(b&1)
			ans=ans*base;
		ans=ans*ans;
		b>>=1;
	}
	return;
}
int qpow(int a,int b,int p){
	a%=p;
	int res=1;
	while(b){
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&ans.a[i][j]);
	for(int i=1;i<=n;i++)
		base.a[i][i]=1;
	qpow(k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			printf("%lld ",ans.a[i][j]%mod);
		printf("\n");
	}
	return 0;
}
