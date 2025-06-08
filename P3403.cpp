#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
}
template<typename T,typename...Args>
void read(T &x,Args &...args){read(x);read(args...);}
typedef long long ll;
constexpr int N=1e5+10;
constexpr ll inf=(1ull<<63)-1;
ll h,dis[N],ans;
int x,y,z,x1[3];
struct edge{
    int v,w;
    edge(int v,int w):v(v),w(w){}
};
vector<edge> e[N];
struct node{
    int u;ll val;
    node(int u,ll val):u(u),val(val){}
    bool operator<(const node &x)const{return val>x.val;}
};
priority_queue<node> q;
bool vis[N];
int main(){
    read(h,x1[0],x1[1],x1[2]);--h;
    sort(x1,x1+3);x=x1[0],y=x1[1],z=x1[2];
    for(int i=0;i<x;i++){
        e[i].push_back(edge((i+y)%x,y));
        e[i].push_back(edge((i+z)%x,z));
        dis[i]=inf;
    }
    dis[0]=0;
    q.push(node(0,0));
    while(!q.empty()){
        int u=q.top().u;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto temp:e[u]){
            int v=temp.v,w=temp.w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push(node(v,dis[v]));
            }
        }
    }
    for(int i=0;i<x;i++)
        if(h>=dis[i]) ans+=(h-dis[i])/x+1;
    printf("%lld\n",ans);
    return 0;
}
