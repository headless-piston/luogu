#include<cstdio>
#include<cstring>
template<typename T>
void read(T &x){
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return;
}
template<typename T,typename...Args>
void read(T &x,Args &...args){
	read(x);
	read(args...);
	return;
}
template<typename T>
T Max(const T &a,const T &b){
	return a<b?b:a;
}
const int N=20;
int n,m,dp[N][1<<18|1],ans,e[N][N];
int main(){
	memset(dp,0xcf,sizeof(dp));
    read(n,m);
	for(int i=1,s,d,l;i<=m;i++){
		read(s,d,l);
		e[s][d]=l;
	}
	dp[0][1]=0;
	for(int i=1;i<(1<<n);i+=2)
		for(int j=0;j<n;j++)
			if(i>>j&1)
				for(int k=1;k<n;k++){
					if((i>>k&1)&&e[j][k])
						dp[k][i]=Max(dp[k][i],dp[j][1<<k^i]+e[j][k]);
					if(k==n-1)
						ans=Max(ans,dp[k][i]);
				}
	printf("%d\n",ans);
    return 0;
}
