#include<cstdio>
#include<cstring>
template<typename T>
void read(T &x){
    bool f=0;
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    if(f)
        x=~x+1;
    return;
}
template<typename T,typename...Args>
void read(T &x,Args &...args){
    read(x);
    read(args...);
    return;
}
template<typename T>
T Min(const T &a,const T &b){
    return a<b?a:b;
}
template<typename T,typename...Args>
T Min(const T &a,const T &b,const Args &...args){
    return Min(Min(a,b),args...);
}
#define inf 0x3f3f3f3f
const int N=10010,M=1010;
int n,m,k,x[N],y[N],dp[N][M],cnt,res;
struct node{
    int l,h;
}c[N];
int main(){
    memset(dp,0x3f,sizeof(dp));
    read(n,m,k);
    for(int i=0;i<n;i++)
        read(x[i],y[i]);
    for(int i=1,p;i<=k;i++){
        read(p);
        read(c[p].l,c[p].h);
    }
    for(int i=1;i<=m;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++){
        for(int j=x[i-1]+1;j<=m;j++)
            dp[i][j]=Min(dp[i][j],dp[i-1][j-x[i-1]]+1,dp[i][j-x[i-1]]+1);
        for(int j=m-x[i-1];j<=m;j++)
            dp[i][m]=Min(dp[i][m],dp[i-1][j]+1,dp[i][j]+1);
        for(int j=1;j+y[i-1]<=m;j++)
            dp[i][j]=Min(dp[i][j],dp[i-1][j+y[i-1]]);
        if(c[i].h){
            cnt++;
            for(int j=1;j<=c[i].l;j++)
                dp[i][j]=inf;
            for(int j=c[i].h;j<=m;j++)
                dp[i][j]=inf;
        }
        bool f=1;
        for(int j=1;j<=m;j++)
            if(dp[i][j]!=inf){
                f=0;
                break;
            }
        if(f){
            printf("0\n%d\n",cnt-1);
            return 0;
        }
    }
    res=inf;
    for(int i=1;i<=m;i++)
        res=Min(res,dp[n][i]);
    printf("1\n%d\n",res);
    return 0;
}