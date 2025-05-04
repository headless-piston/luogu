#include<cstdio>
#include<cmath>
#include<algorithm>
#define eps 1e-8
using std::swap;
const int N=110;
int n;
double matrix[N][N],ans[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%lf",&matrix[i][j]);
	for(int i=1;i<=n;i++){
		int r=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(matrix[r][i])<fabs(matrix[j][i]))
				r=j;//寻找主元 
		if(fabs(matrix[r][i])<eps){
			printf("No Solution");//若主元为0，方程组无解或无穷多解 
			return 0;
		}
		if(i!=r)
			swap(matrix[i],matrix[r]);
		double div=matrix[i][i];
		for(int j=i;j<=n+1;j++)
			matrix[i][j]/=div;
		for(int j=i+1;j<=n;j++){
			div=matrix[j][i];
			for(int k=i;k<=n+1;k++)
				matrix[j][k]-=matrix[i][k]*div;
		}//消元
	}
	ans[n]=matrix[n][n+1];
	for(int i=n-1;i;i--){
		ans[i]=matrix[i][n+1];
		for(int j=i+1;j<=n;j++)
			ans[i]-=matrix[i][j]*ans[j];
	}//回代
	for(int i=1;i<=n;i++)
		printf("%.2lf\n",ans[i]);
	return 0;
}
