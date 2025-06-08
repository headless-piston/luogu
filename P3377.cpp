#include<cstdio>
#include<queue>
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
}
template<typename T,typename...Args>
void read(T &x,Args &...args){read(x);read(args...);}
constexpr int N=1e5+10;
typedef pair<int,int> pr;
priority_queue<pr,vector<pr>,greater<pr>> q[N];
int n,m,fa[N],op,x,y;
bool del[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    read(n,m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,a;i<=n;i++) read(a),q[i].push(make_pair(a,i));
    while(m--){
        read(op,x);
        if(op&1){
            read(y);
            if(del[x]||del[y]) continue;
            x=find(x),y=find(y);
            if(x==y) continue;
            if(q[x].size()<q[y].size()) swap(x,y);
            while(!q[y].empty()) q[x].push(q[y].top()),q[y].pop();
            fa[y]=x;
        }
        else{
            if(del[x]){
                printf("-1\n");
                continue;
            }
            x=find(x);
            del[q[x].top().second]=1;
            printf("%d\n",q[x].top().first);
            q[x].pop();
        }
    }
    return 0;
}
