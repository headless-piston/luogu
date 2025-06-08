#include<cstdio>
template<typename T>
void read(T &x){
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
template<typename T>
inline void Swap(T &a,T &b){T c=a;a=b;b=c;}
constexpr int N=1e6+10;
typedef long long ll;
int n,m;
struct node{
    int ls,rs,dist;
    ll val;
    node(){ls=rs=dist=val=0;}
    node(ll val):ls(0),rs(0),dist(0),val(val){}
}tree[N];
int fa[N],root[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void push_up(int u){
    if(tree[tree[u].ls].dist<tree[tree[u].rs].dist) Swap(tree[u].ls,tree[u].rs);
    tree[u].dist=tree[tree[u].rs].dist+1;
}
int merge(int x,int y){
    if(!x||!y) return x|y;
    if(tree[x].val>tree[y].val) Swap(x,y);
    tree[x].rs=merge(tree[x].rs,y);
    push_up(x);
    return x;
}
int erase(int x,int y){
    if(x==0) return 0;
    if(x==y) return merge(tree[x].ls,tree[x].rs);
    tree[x].ls=erase(tree[x].ls,y);
    tree[x].rs=erase(tree[x].rs,y);
    push_up(x);
    return x;
}
int op,x,y;
ll z;
int main(){
    read(n,m);
    for(int i=1,a;i<=n;i++){
        read(a);
        fa[i]=root[i]=i;
        tree[i].val=a;
    }
    while(m--){
        read(op,x);
        if(op==0){
            read(y);
            x=find(x);
            root[x]=erase(root[x],y);
        }
        else if(op==1){
            x=find(x);
            printf("%lld\n",tree[root[x]].val);
        }
        else if(op==2){
            read(y);
            x=find(x),y=find(y);
            if(x==y) continue;
            root[x]=merge(root[x],root[y]);
            root[y]=0;
            fa[y]=x;
        }
        else{
            read(y,z);
            x=find(x);
            root[x]=erase(root[x],y);
            tree[y]=node(z);
            root[x]=merge(root[x],y);
        }
    }
    return 0;
}
