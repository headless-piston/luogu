#include<cstdio>
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
const int N=1e5+10;
int n,k;
struct node{
    int a,b,c;
    bool operator<(const node &x)const{
        return a==x.a?(b==x.b?c<x.c:b<x.b):a<x.a;
    }
}m[N];
struct Segtree{
    int ls,rs,sum;
}segtree[N*100];
#define ls segtree[u].ls
#define rs segtree[u].rs
#define lowbit(x) (x&-x)
int tot,root[2*N];
void push_up(int u){
    segtree[u].sum=segtree[ls].sum+segtree[rs].sum;
    return;
}
void seg_modify(int &u,int l,int r,int x,int val){
    if(!u)
        u=++tot;
    if(l==r){
        segtree[u].sum+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)
        seg_modify(ls,l,mid,x,val);
    else
        seg_modify(rs,mid+1,r,x,val);
    push_up(u);
    return;
}
int seg_query(int u,int l,int r,int x,int y){
    if(!u)
        return 0;
    if(x<=l&&y>=r)
        return segtree[u].sum;
    int res=0,mid=(l+r)>>1;
    if(x<=mid)
        res+=seg_query(ls,l,mid,x,y);
    if(y>mid)
        res+=seg_query(rs,mid+1,r,x,y);
    return res;
}
void BIT_modify(int x,int y,int val){
    if(x==0)
        return;
    for(int i=x;i<=k;i+=lowbit(i))
        seg_modify(root[i],1,k,y,val);
    return;
}
int BIT_query(int x,int y){
    int res=0;
    for(int i=x;i;i^=lowbit(i))
        res+=seg_query(root[i],1,k,1,y);
    return res;
}
int sum,res[N];
int main(){
    read(n,k);
    for(int i=1;i<=n;i++)
        read(m[i].a,m[i].b,m[i].c);
    sort(m+1,m+1+n);
    for(int i=1,cnt=1;i<=n;i++){
        if(m[i].a==m[i+1].a&&m[i].b==m[i+1].b&&m[i].c==m[i+1].c){
            cnt++;
            continue;
        }
        BIT_modify(m[i].b,m[i].c,cnt);
        sum=BIT_query(m[i].b,m[i].c);
        res[sum]+=cnt;
        cnt=1;
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",res[i]);
    return 0;
}
