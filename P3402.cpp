#include<cstdio>
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
void Swap(T &a,T &b){
    T c=a;
    a=b;
    b=c;
    return;
}
const int N=1e5+10,M=2e5+10;
struct Tree{
    int ls,rs,fa,dep;
}tree[N*50];
int nodetot,root[M],n,m;
void build(int &u,int l,int r){
    u=++nodetot;
    if(l==r){
        tree[u].fa=l;
        tree[u].dep=1;
        return;
    }
    int mid=(l+r)/2;
    build(tree[u].ls,l,mid);
    build(tree[u].rs,mid+1,r);
    return;
}
void modify_fa(int old,int &u,int l,int r,int x,int k){
    u=++nodetot;
    tree[u]=tree[old];
    if(l==r){
        tree[u].fa=k;
        return;
    }
    int mid=(l+r)/2;
    if(x<=mid)
        modify_fa(tree[old].ls,tree[u].ls,l,mid,x,k);
    else
        modify_fa(tree[old].rs,tree[u].rs,mid+1,r,x,k);
    return;
}
void modify_dep(int old,int &u,int l,int r,int x){
    u=++nodetot;
    tree[u]=tree[old];
    if(l==r){
        tree[u].dep++;
        return;
    }
    int mid=(l+r)/2;
    if(x<=mid)
        modify_dep(tree[old].ls,tree[u].ls,l,mid,x);
    else
        modify_dep(tree[old].rs,tree[u].rs,mid+1,r,x);
    return;
}
int query_fa(int u,int l,int r,int x){
    if(l==r)
        return tree[u].fa;
    int mid=(l+r)/2;
    if(x<=mid)
        return query_fa(tree[u].ls,l,mid,x);
    else
        return query_fa(tree[u].rs,mid+1,r,x);
}
int query_dep(int u,int l,int r,int x){
    if(l==r)
        return tree[u].dep;
    int mid=(l+r)/2;
    if(x<=mid)
        return query_dep(tree[u].ls,l,mid,x);
    else
        return query_dep(tree[u].rs,mid+1,r,x);
}
int find(int ver,int x){
    int fx=query_fa(root[ver],1,n,x);
    if(fx==x)
        return x;
    return find(ver,fx);
}
void merge(int ver,int x,int y){
    x=find(ver-1,x);
    y=find(ver-1,y);
    if(x==y){
        root[ver]=root[ver-1];
        return;
    }
    int depx=query_dep(root[ver-1],1,n,x),depy=query_dep(root[ver-1],1,n,y);
    if(depx>depy)
        Swap(x,y);
    modify_fa(root[ver-1],root[ver],1,n,x,y);
    if(depx==depy)
        modify_dep(root[ver],root[ver],1,n,y);
    return;
}
int opt,a,b;
int main(){
    read(n,m);
    build(root[0],1,n);
    for(int i=1;i<=m;i++){
        read(opt);
        if(opt==1){
            read(a,b);
            merge(i,a,b);
        }
        else if(opt==2){
            read(a);
            root[i]=root[a];
        }
        else{
            read(a,b);
            root[i]=root[i-1];
            if(find(i,a)==find(i,b))
                printf("1\n");
            else
                printf("0\n");
        }
    }
    return 0;
}