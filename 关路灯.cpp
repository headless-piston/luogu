#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,c,p[60],w[60],dp[60][60][2],sum[60];
int main(){
	memset(dp,0x3f,sizeof(dp));
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i],&w[i]);
		sum[i]=sum[i-1]+w[i];
	}
	dp[c][c][0]=dp[c][c][1]=0;
	for(int len=2;len<=n;len++)
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			dp[l][r][0]=min(dp[l+1][r][0]+(p[l+1]-p[l])*(sum[l]+sum[n]-sum[r]),\
			dp[l+1][r][1]+(p[r]-p[l])*(sum[l]+sum[n]-sum[r]));
			dp[l][r][1]=min(dp[l][r-1][0]+(p[r]-p[l])*(sum[l-1]+sum[n]-sum[r-1]),\
			dp[l][r-1][1]+(p[r]-p[r-1])*(sum[l-1]+sum[n]-sum[r-1]));
		}
	printf("%d",min(dp[1][n][1],dp[1][n][0]));
	return 0;
}
