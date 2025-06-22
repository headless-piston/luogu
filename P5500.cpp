#include<cstdio>
#include<algorithm>
using std::max;
using std::min;
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
constexpr int N=2e5+10;
int n,m;
struct Seg{
    int maxn,maxl,maxr,tag,vall,valr,len;
    Seg(int maxn=0,int maxl=0,int maxr=0,int tag=0,int vall=0,int valr=0,int len=0):
    maxn(maxn),maxl(maxl),maxr(maxr),tag(tag),vall(vall),valr(valr),len(len){}
    friend Seg operator+(const Seg &a,const Seg &b){
        if(!a.len) return b;
        if(!b.len) return a;
        Seg res;
        res.maxn=max(a.maxn,b.maxn);
        res.maxl=a.maxl,res.maxr=b.maxr;
        res.vall=a.vall,res.valr=b.valr;
        res.len=a.len+b.len;
        if(a.valr==b.vall){
            res.maxn=max(res.maxn,a.maxr+b.maxl);
            if(a.maxl==a.len) res.maxl+=b.maxl;
            if(b.maxr==b.len) res.maxr+=a.maxr;
        }
        return res;
    }
}tree[N<<2];
#define ls (u<<1)
#define rs (u<<1|1)
void build(int u,int l,int r){
    if(l==r){
        int val;
        read(val);
        tree[u]=Seg(1,1,1,0,val,val,1);
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    tree[u]=tree[ls]+tree[rs];
}
inline void push_down(int u){
    if(!tree[u].tag) return;
    int lenl=tree[ls].len,lenr=tree[rs].len,val=tree[u].tag;
    tree[ls]=Seg(lenl,lenl,lenl,val,val,val,lenl);
    tree[rs]=Seg(lenr,lenr,lenr,val,val,val,lenr);
    tree[u].tag=0;
}
void modify(int u,int l,int r,int x,int y,int k){
    if(x<=l&&y>=r){
        int len=tree[u].len;
        tree[u]=Seg(len,len,len,k,k,k,len);
        return;
    }
    push_down(u);
    int mid=(l+r)>>1;
    if(x<=mid) modify(ls,l,mid,x,y,k);
    if(y>mid) modify(rs,mid+1,r,x,y,k);
    tree[u]=tree[ls]+tree[rs];
}
Seg query(int u,int l,int r,int x,int y){
    if(x<=l&&y>=r) return tree[u];
    Seg res;
    push_down(u);
    int mid=(l+r)>>1;
    if(x<=mid) res=res+query(ls,l,mid,x,y);
    if(y>mid) res=res+query(rs,mid+1,r,x,y);
    return res;
}
int x,y,k;
int main(){
    read(n,m);
    build(1,1,n);
    while(m--){
        char ch=getchar();
        while(ch!='R'&&ch!='Q') ch=getchar();
        read(x,y,k);
        if(ch^'Q') modify(1,1,n,x,y,k);
        else if(k==0)
            printf("%d\n",query(1,1,n,x,y).maxn);
        else{
            Seg temp=query(1,1,n,x,y);
            int res=temp.maxn;
            if(temp.vall==temp.valr) res=max(res,temp.maxl+temp.maxr);
            printf("%d\n",min(res,temp.len));
        }
    }
    return 0;
}
