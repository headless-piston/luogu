#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
template<typename T>
inline void read(T &x){
    bool f=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    if(f) x=~x+1;
}
template<typename T,typename...Args>
void read(T &x,Args &...args){read(x);read(args...);}
typedef long long ll;
constexpr int mod=1e9+7,N=1e5+10;
struct modint{
    int val;
    modint(int val=0):val(val){}
    modint operator+(const modint &x)const{return modint((val+x.val)%mod);}
    modint &operator+=(const modint &x){val+=x.val;val%=mod;return *this;}
    modint operator*(const modint &x)const{return modint((ll)val*x.val%mod);}
};
vector<int> e[N];
int n,k,siz[N];
modint dp[N][110][2][2],temp[110][2][2];
void dfs(int u,int fa){
    dp[u][1][1][0]=dp[u][0][0][0]=1;
    siz[u]=1;
    for(int v:e[u]){
        if(v==fa) continue;
        dfs(v,u);
        for(int i=0;i<=k;i++){
            temp[i][0][0]=dp[u][i][0][0];
            temp[i][0][1]=dp[u][i][0][1];
            temp[i][1][0]=dp[u][i][1][0];
            temp[i][1][1]=dp[u][i][1][1];
            dp[u][i][0][0]=dp[u][i][0][1]=dp[u][i][1][0]=dp[u][i][1][1]=0;
        }
        for(int i=0;i<=min(siz[u],k);i++)
            for(int j=0;j<=min(siz[v],k-i);j++){
                dp[u][i+j][0][0]+=temp[i][0][0]*dp[v][j][0][1];
                dp[u][i+j][1][0]+=temp[i][1][0]*(dp[v][j][0][0]+dp[v][j][0][1]);
                dp[u][i+j][0][1]+=temp[i][0][0]*dp[v][j][1][1]+
                temp[i][0][1]*(dp[v][j][0][1]+dp[v][j][1][1]);
                dp[u][i+j][1][1]+=temp[i][1][0]*(dp[v][j][1][0]+dp[v][j][1][1])+
                temp[i][1][1]*(dp[v][j][0][0]+dp[v][j][0][1]+dp[v][j][1][0]+dp[v][j][1][1]);
            }
        siz[u]+=siz[v];
    }
}
int main(){
    read(n,k);
    for(int i=1,u,v;i<n;i++){
        read(u,v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    printf("%d\n",(dp[1][k][0][1]+dp[1][k][1][1]).val);
    return 0;
}
