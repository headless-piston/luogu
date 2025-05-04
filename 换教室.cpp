#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2010,M=90010;
int n,m,v,e;
int c[N],d[N],edge[310][310];
double k[N],dp[2010][2010][2],ans;
int main(){
	memset(edge,0x3f,sizeof(edge));
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			dp[i][j][0]=dp[i][j][1]=1145141919810;
	for(int i=1;i<=n;i++)
		scanf("%d",c+i);
	for(int i=1;i<=n;i++)
		scanf("%d",d+i);
	for(int i=1;i<=n;i++)
		scanf("%lf",k+i);
	for(int i=1;i<=e;i++){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		edge[a][b]=min(edge[a][b],w);
		edge[b][a]=min(edge[b][a],w);
	}
	for(int i=1;i<=v;i++)
		edge[i][i]=0;
	for(int k1=1;k1<=v;k1++)
		for(int i=1;i<=v;i++)
			for(int j=1;j<=v;j++)
				edge[i][j]=min(edge[i][j],edge[i][k1]+edge[k1][j]);
	dp[1][0][0]=dp[1][1][1]=0;
	for(int i=2;i<=n;i++)
		for(int j=0;j<=m;j++){
			dp[i][j][0]=min(dp[i-1][j][1]+k[i-1]*edge[d[i-1]][c[i]]+\
					(1-k[i-1])*edge[c[i-1]][c[i]],\
				dp[i-1][j][0]+edge[c[i-1]][c[i]]);
			if(j){
				dp[i][j][1]=min(dp[i-1][j-1][1]+k[i-1]*k[i]*edge[d[i-1]][d[i]]+\
						k[i-1]*(1-k[i])*edge[d[i-1]][c[i]]+\
						(1-k[i-1])*k[i]*edge[c[i-1]][d[i]]+\
						(1-k[i-1])*(1-k[i])*edge[c[i-1]][c[i]],\
					dp[i-1][j-1][0]+k[i]*edge[c[i-1]][d[i]]+\
						(1-k[i])*edge[c[i-1]][c[i]]);
			}
		}
	ans=1145141919810;
	for(int i=0;i<=m;i++)
		ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
	printf("%.2lf",ans);
	return 0;
}
