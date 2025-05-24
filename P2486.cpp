#include<iostream>
#include<set>
#include<vector>
using namespace std;
struct node{
    int l,r;
    int val;
    node(int l,int r=0,int val=0):l(l),r(r),val(val){}
    bool operator<(const node &x)const{
        return l<x.l;
    }
};
set<node> odt;
auto split(int pos){
    auto it=odt.lower_bound(node(pos));
    if(it!=odt.end()&&it->l==pos)
        return it;
    it--;
    int l=it->l,r=it->r,val=it->val;
    odt.erase(it);
    odt.insert(node(l,pos-1,val));
    return odt.insert(node(pos,r,val)).first;
}
void assign(int l,int r,int val){
    auto itr=split(r+1),itl=split(l);
    odt.erase(itl,itr);
    odt.insert(node(l,r,val));
    return;
}
const int N=1e5+10;
int n,m,c[N];
vector<int> e[N];
int fa[N],top[N],dfn[N],dfncnt,son[N],dep[N],siz[N];
void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    siz[u]=1;
    fa[u]=f;
    for(int v:e[u]){
        if(v==f)
            continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])
            son[u]=v;
    }
    return;
}
void dfs2(int u,int topf){
    top[u]=topf;
    dfn[u]=++dfncnt;
    if(son[u])
        dfs2(son[u],topf);
    for(int v:e[u]){
        if(v==son[u]||v==fa[u])
            continue;
        dfs2(v,v);
    }
    return;
}
void modify(int x,int y,int k){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        assign(dfn[top[x]],dfn[x],k);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    assign(dfn[x],dfn[y],k);
    return;
}
int ask(int x,int y){
    int res=0,prea=0,preb=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            auto itr=split(dfn[x]+1),itl=split(dfn[top[x]]);
            for(itr--;;itr--){
                if(itr->val!=prea)
                    res++;
                prea=itr->val;
                if(itl==itr)
                    break;
            }
            x=fa[top[x]];
        }
        else{
            auto itr=split(dfn[y]+1),itl=split(dfn[top[y]]);
            for(itr--;;itr--){
                if(itr->val!=preb)
                    res++;
                preb=itr->val;
                if(itl==itr)
                    break;
            }
            y=fa[top[y]];
        }
    }
    if(dep[x]>dep[y]){
        auto itr=split(dfn[x]+1),itl=split(dfn[y]);
        for(itr--;;itr--){
            if(itr->val!=prea)
                res++;
            prea=itr->val;
            if(itl==itr)
                break;
        }
    }
    else{
        auto itr=split(dfn[y]+1),itl=split(dfn[x]);
        for(itr--;;itr--){
            if(itr->val!=preb)
                res++;
            preb=itr->val;
            if(itl==itr)
                break;
        }
    }
    if(prea==preb)
        res--;
    return res;
}
char op;
int x,y,k;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>c[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++)
        odt.insert(node(dfn[i],dfn[i],c[i]));
    while(m--){
        cin>>op>>x>>y;
        if(op^'Q'){
            cin>>k;
            modify(x,y,k);
        }
        else
            cout<<ask(x,y)<<'\n';
    }
    return 0;
}
