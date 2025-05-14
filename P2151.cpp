#include<cstdio>
#include<cstring>
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
void write(T x){
    if(x<0){
        x=~x+1;
        putchar('-');
    }
    if(x<10)
        putchar(x+48);
    else{
        write(x/10);
        putchar(x%10+48);
    }
    return;
}
#define mod 45989
const int N=310;
int cnt;
struct Matrix{
    int x[N][N];
    Matrix(){
        memset(x,0,sizeof(x));
    }
    Matrix operator*(const Matrix &a){
        Matrix res;
        for(int i=1;i<=cnt;i++)
            for(int j=1;j<=cnt;j++)
                for(int k=1;k<=cnt;k++)
                    res.x[i][j]=(res.x[i][j]+x[i][k]*a.x[k][j]%mod)%mod;
        return res;
    }
}p;
int n,m,t,a,b,res;
Matrix qpow(Matrix a,int b){
    Matrix res;
    for(int i=1;i<=cnt;i++)
        res.x[i][i]=1;
    while(b){
        if(b&1)
            res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}
struct edge{
    int u,v;
}e[N];
int main(){
    read(n,m,t,a,b);
    a++,b++;
    e[cnt=1].u=0,e[1].v=a;
    for(int i=1,u,v;i<=m;i++){
        read(u,v);
        u++,v++;
        e[++cnt].u=u;
        e[cnt].v=v;
        e[++cnt].u=v;
        e[cnt].v=u;
    }
    for(int i=1;i<=cnt;i++)
        for(int j=1;j<=cnt;j++)
            if(e[i].v==e[j].u&&i!=(j^1)&&i!=j)
                p.x[i][j]=1;
    p=qpow(p,t);
    for(int i=1;i<=cnt;i++)
        if(e[i].v==b)
            res=(res+p.x[1][i])%mod;
    write(res);
    putchar('\n');
    return 0;
}