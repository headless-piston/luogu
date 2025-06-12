#include<cstdio>
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
template<typename T>
inline void Swap(T &a,T &b){T c=a;a=b;b=c;}
typedef long long ll;
constexpr int N=3e5+10;
int n,m,f[N],a[N],dist[N],ls[N],rs[N],root[N],dep[N],c[N],die[N],die_dep[N];
ll h[N],v[N],s[N],add[N],mul[N];
inline void push_up(int u){
    if(dist[ls[u]]<dist[rs[u]]) Swap(ls[u],rs[u]);
    dist[u]=dist[rs[u]]+1;
}
inline void push_down(int u){
    if(!add[u]&&mul[u]==1) return;
    if(ls[u]){
        mul[ls[u]]*=mul[u];
        add[ls[u]]*=mul[u];
        add[ls[u]]+=add[u];
        s[ls[u]]*=mul[u];
        s[ls[u]]+=add[u];
    }
    if(rs[u]){
        mul[rs[u]]*=mul[u];
        add[rs[u]]*=mul[u];
        add[rs[u]]+=add[u];
        s[rs[u]]*=mul[u];
        s[rs[u]]+=add[u];
    }
    add[u]=0,mul[u]=1;
}
int merge(int x,int y){
    if(!x||!y) return x|y;
    push_down(x);push_down(y);
    if(s[x]>s[y]) Swap(x,y);
    rs[x]=merge(rs[x],y);
    push_up(x);
    return x;
}
int main(){
    read(n,m);
    for(int i=1;i<=n;i++) read(h[i]);
    dep[1]=1;
    for(int i=2;i<=n;i++){
        read(f[i],a[i],v[i]);
        dep[i]=dep[f[i]]+1;
    }
    for(int i=1;i<=m;i++){
        read(s[i],c[i]);
        mul[i]=1;
        root[c[i]]=merge(root[c[i]],i);
    }
    for(int i=n;i;i--){
        while(root[i]&&s[root[i]]<h[i]){
            ++die[i];
            die_dep[root[i]]=dep[i];
            push_down(root[i]);
            root[i]=merge(ls[root[i]],rs[root[i]]);
        }
        if(i==1||!root[i]) continue;
        int u=root[i];
        if(a[i]) mul[u]*=v[i],add[u]*=v[i],s[u]*=v[i];
        else add[u]+=v[i],s[u]+=v[i];
        push_down(root[i]);
        root[f[i]]=merge(root[f[i]],root[i]);
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",die[i]);
    for(int i=1;i<=m;i++)
        printf("%d\n",dep[c[i]]-die_dep[i]);
    return 0;
}
