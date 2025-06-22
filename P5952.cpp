#include<cstdio>
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
constexpr int N=5e5+10,mod=1e9+7;
struct edge{
    int u,v,val;
    edge(int u=0,int v=0,int val=0):u(u),v(v),val(val){}
    bool operator<(const edge &x)const{return val<x.val;}
}e[N<<1];
int n,m,H,tot,fa[N],ans[N],h[N],cnt;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline int getid(int x,int y){return (x-1)*m+y;}
int main(){
    read(n,m,H);
    for(int i=1;i<=n*m;i++) fa[i]=i,ans[i]=1;
    for(int i=1;i<=n;i++)
        for(int j=1,val;j<m;j++){
            read(val);
            e[++tot]=edge(getid(i,j),getid(i,j+1),val);
        }
    for(int i=1;i<n;i++)
        for(int j=1,val;j<=m;j++){
            read(val);
            e[++tot]=edge(getid(i,j),getid(i+1,j),val);
        }
    sort(e+1,e+1+tot);
    for(int i=1;i<=tot;i++){
        int x=find(e[i].u),y=find(e[i].v),val=e[i].val;
        if(x!=y){
            ans[x]=((long long)ans[x]-h[x]+val)*(ans[y]-h[y]+val)%mod;
            h[x]=val;
            fa[y]=x;
            if(++cnt==n*m-1) break;
        }
    }
    int id=find(getid(1,1));
    printf("%lld\n",((long long)ans[id]-h[id]+H)%mod);
    return 0;
}
