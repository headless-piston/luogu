#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
double a[12][12],b[12][12],ans[12];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&a[i][j]);
	for(int i=1;i<=n;i++){
		double sum=0;
		for(int j=1;j<=n;j++){
			b[i][j]=2*(a[i][j]-a[i+1][j]);
			sum+=a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j];
		}
		b[i][n+1]=sum;
	}
	for(int i=1;i<=n;i++){
		double div=b[i][i];
		for(int j=i;j<=n+1;j++)
			b[i][j]/=div;
		for(int j=i+1;j<=n;j++){
			div=b[j][i];
			for(int k=i;k<=n+1;k++)
				b[j][k]-=b[i][k]*div;
		}
	}
	ans[n]=b[n][n+1];
	for(int i=n-1;i;i--){
		ans[i]=b[i][n+1];
		for(int j=i+1;j<=n;j++)
			ans[i]-=b[i][j]*ans[j];
	}
	for(int i=1;i<=n;i++)
		printf("%.3lf ",ans[i]);
	return 0;
}
