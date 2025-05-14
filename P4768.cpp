#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
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
const int N=2e5+10,M=4e5+10;
int t;
struct node{
    int u,v,a;
    bool operator<(const node &x)const{
        return a>x.a;
    }
}p[M*2];
struct edge{
    int to,nxt,w;
}e[M*2];
int tot_edge,head[N];
void add_edge(int u,int v,int w){
    e[++tot_edge].to=v;
    e[tot_edge].w=w;
    e[tot_edge].nxt=head[u];
    head[u]=tot_edge;
    return;
}
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> que;
int dis[N*2];
bool vis[N];
void dijkstra(){
    dis[1]=0;
    que.push(make_pair(0,1));
    while(!que.empty()){
        int u=que.top().second;
        que.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to,w=e[i].w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
		        que.push(make_pair(dis[v],v));
            }
        }
    }
    return;
}
int n,m,q,k,s,fa[M*2],w[M*2],f[M*2][21];
int find(int x){
    if(fa[x]==x)
        return x;
    return fa[x]=find(fa[x]);
}
void kruskal(){
    int cnt=n;
    sort(p+1,p+1+m);
    for(int i=1;i<=n*2;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++){
        int x=find(p[i].u),y=find(p[i].v);
        if(x==y)
            continue;
        fa[x]=fa[y]=++cnt;
        w[cnt]=p[i].a;
        dis[cnt]=Min(dis[x],dis[y]);
        f[x][0]=f[y][0]=cnt;
    }
    for(int i=1;(1<<i)<=cnt;i++)
        for(int j=1;j<=cnt;j++)
            f[j][i]=f[f[j][i-1]][i-1];
    return;
}
int lastans,v0,p0;
int query(int x,int y){
    for(int i=20;i>=0;i--)
        if(f[x][i]&&w[f[x][i]]>y)
            x=f[x][i];
    return dis[x];
}
int main(){
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
    read(t);
    while(t--){
		tot_edge=lastans=0;
		memset(w,0,sizeof(w));
		memset(f,0,sizeof(f));
		memset(dis,0x3f,sizeof(dis));
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
        read(n,m);
        for(int i=1,l;i<=m;i++){
            read(p[i].u,p[i].v,l,p[i].a);
            add_edge(p[i].u,p[i].v,l);
            add_edge(p[i].v,p[i].u,l);
        }
        dijkstra();
        kruskal();
        read(q,k,s);
        while(q--){
            read(v0,p0);
            v0=(v0+k*lastans-1)%n+1;
            p0=(p0+k*lastans)%(s+1);
            lastans=query(v0,p0);
            printf("%d\n",lastans);
        }
    }
    return 0;
}
