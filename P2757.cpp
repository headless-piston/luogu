#include<cstdio>
#include<cstring>
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
template<typename T>
inline T Min(const T &a,const T &b){return a<b?a:b;}
constexpr int N=5e5+10,base=13331;
typedef unsigned long long ull;
int t,n,p,a[N];
ull b[N];
struct Tree{
    ull hash1,hash2;
    int len;
    Tree():hash1(0),hash2(0),len(0){}
    Tree(ull hash1,ull hash2,int len):hash1(hash1),hash2(hash2),len(len){}
    friend Tree operator+(const Tree &x,const Tree &y){
        Tree res;
        res.hash1=x.hash1+y.hash1*b[x.len];
        res.hash2=x.hash2*b[y.len]+y.hash2;
        res.len=x.len+y.len;
        return res;
    }
}tree[N*3];
inline void modify(int x){
    x+=p;tree[x]=Tree(1,1,1);
    for(x>>=1;x;x>>=1) tree[x]=tree[x<<1]+tree[x<<1|1];
}
inline Tree query(int l,int r){
    l+=p-1,r+=p+1;
    Tree resl,resr;
    while(l^1^r){
        if(~l&1) resl=resl+tree[l^1];
        if(r&1) resr=tree[r^1]+resr;
        l>>=1,r>>=1;
    }
    return resl+resr;
}
inline bool check(){
    for(int i=1;i<=n;i++){
        modify(a[i]);
        int len=Min(a[i]-1,n-a[i]);
        if(len<=0) continue;
        if(query(a[i]+1,a[i]+len).hash1!=query(a[i]-len,a[i]-1).hash2) return 1;
    }
    return 0;
}
int main(){
    b[0]=1;
    for(int i=1;i<=5e5;i++) b[i]=b[i-1]*base;
    read(t);
    while(t--){
        read(n);
        for(int i=1;i<=(p<<1);i++) tree[i]=Tree();
        p=1;while(p<=n+1) p<<=1;
        for(int i=1;i<=n;i++) tree[p+i]=Tree(0,0,1),read(a[i]);
        for(int i=p-1;i;i--) tree[i]=tree[i<<1]+tree[i<<1|1];
        if(check()) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
