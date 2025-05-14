#include<cstdio>
#include<algorithm>
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
#define mod 1000000007
const int N=1e5+10;
int n,m,f[N][25],l1,r1,l2,r2,ans,maxn;
int find(int x,int k){
    if(x==f[x][k])
        return x;
    return f[x][k]=find(f[x][k],k);
}
void merge(int x,int y,int k){
    int a=find(x,k),b=find(y,k);
    if(a!=b)
        f[a][k]=b;
    return;
}
bool flag=1;
int main(){
    read(n,m);
    maxn=std::__lg(n);
    for(int i=1;i<=n;i++)
        for(int j=0;j<=maxn;j++)
            f[i][j]=i;
    while(m--){
        read(l1,r1,l2,r2);
        for(int j=maxn;j>=0;j--)
            if(l1+(1<<j)-1<=r1){
                merge(l1,l2,j);
                l1+=1<<j;
                l2+=1<<j;
            }
    }
    for(int j=maxn;j;j--)
        for(int i=1;i+(1<<j)-1<=n;i++){
            int x=find(i,j);
            merge(i,x,j-1);
            merge(i+(1<<(j-1)),x+(1<<(j-1)),j-1);
        }
    for(int i=1;i<=n;i++)
        if(f[i][0]==i){
            if(flag){
                ans=9;
                flag=0;
            }
            else
                ans=(ans*10ll)%mod;
        }
    printf("%d\n",ans);
    return 0;
}