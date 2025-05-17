#include<cstdio>
#include<cmath>
#include<cstring>
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
template<typename T>
inline void read(T &x){
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return;
}
template<typename T>
void write(T x){
    if(x>9)
        write(x/10);
    putchar(x%10^48);
    return;
}
template<typename T,typename...Args>
void read(T &x,Args &...args){
    read(x);
    read(args...);
    return;
}
template<typename T>
inline T Min(const T &a,const T &b){
    return a<b?a:b;
}
template<typename T>
inline T Max(const T &a,const T &b){
    return a<b?b:a;
}
const int N=1e6+10,M=5e5+10,V=1e5+10;
int n,m,a[N],block,tot;
int op[M],ql[M],qr[M],qx[M],res[M],maxn;
int fa[V],siz[V],tag,l,r,zero[N];
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y)
        return;
    fa[x]=y;
    siz[y]+=siz[x];
    siz[x]=0;
    return;
}
inline void build(){
    memset(siz+tag,0,sizeof(int)*(maxn-tag+1));
    tag=maxn=0;
    for(int i=l;i<=r;i++){
        maxn=Max(maxn,a[i]);
        siz[a[i]]++;
    }
    for(int i=0;i<=maxn;i++)
        fa[i]=i;
    return;
}
inline void init(){
    read(n,m);
    block=sqrt(n);
    tot=n/block;
    if(n%block)
        tot++;
    for(int i=1;i<=n;i++){
        read(a[i]);
        if(!a[i])
            zero[i]=1;
        zero[i]+=zero[i-1];
    }
    for(int i=1;i<=m;i++){
        read(op[i],ql[i],qr[i],qx[i]);
        if((~op[i]&1)&&!qx[i])
            res[i]=zero[qr[i]]-zero[ql[i]-1];
    }
    return;
}
int main(){
    init();
    for(int i=1;i<=tot;i++){
        l=(i-1)*block+1,r=Min(i*block,n);
        build();
        for(int j=1;j<=m;j++){
            int x=qx[j];
            if(qr[j]<l||ql[j]>r||x==0)
                continue;
            if(op[j]&1){
                if(x>=maxn-tag)
                    continue;
                if(ql[j]<=l&&qr[j]>=r){
                    if(maxn-tag>=(x<<1)){
                        for(int k=tag+1;k<=x+tag;k++)
                            merge(k,k+x);
                        tag+=x;
                    }
                    else{
                        for(int k=maxn;k>x+tag;k--)
                            merge(k,k-x);
                        while(!siz[maxn]&&maxn>0)
                            maxn--;
                    }
                }
                else{
                    for(int k=l;k<=r;k++)
                        while(fa[a[k]]!=a[k])
                            a[k]=fa[a[k]];
                    for(int k=Max(l,ql[j]);k<=Min(r,qr[j]);k++)
                        if(a[k]-tag>x){
                            siz[a[k]]--;
                            a[k]-=x;
                            siz[a[k]]++;
                        }
                    while(!siz[maxn]&&maxn>0)
                        maxn--;
                }
            }
            else{
                if(x>maxn-tag)
                    continue;
                if(ql[j]<=l&&qr[j]>=r)
                    res[j]+=siz[x+tag];
                else{
                    for(int k=l;k<=r;k++)
                        while(fa[a[k]]!=a[k])
                            a[k]=fa[a[k]];
                    for(int k=Max(l,ql[j]);k<=Min(r,qr[j]);k++)
                        if(a[k]-tag==x)
                            res[j]++;
                }
            }
        }
    }
    for(int i=1;i<=m;i++)
        if(~op[i]&1)
            write(res[i]),putchar('\n');
    return 0;
}
/*
10 10
5 2 5 8 4 0 8 5 3 9 
1 3 10 1
2 9 10 0
2 5 10 4
2 1 9 1
1 2 5 7
1 1 2 9
2 3 6 0
1 9 9 9
2 2 6 8
1 6 6 3

0 1 0 1 0
*/