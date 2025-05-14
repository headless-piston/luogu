#include<cstdio>
#include<vector>
#include<set>
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
typedef long long ll;
const int N=1e5+10;
int n,m;
ll ans,d[N];
int dfn[N],son[N],dfncnt,idfn[N],dep[N],siz[N],top[N],fa[N];
struct edge{
    int to,w;
};
vector<edge> e[N];
set<int> st;
void dfs1(int u,int f){
    siz[u]=1;
    fa[u]=f;
    dep[u]=dep[f]+1;
    for(auto i:e[u]){
        int v=i.to,w=i.w;
        if(v==f)
            continue;
        d[v]=d[u]+w;
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
    idfn[dfncnt]=u;
    if(!son[u])
        return;
    dfs2(son[u],topf);
    for(auto i:e[u]){
        int v=i.to;
        if(v==fa[u]||v==son[u])
            continue;
        dfs2(v,v);
    }
    return;
}
int lca(int a,int b){
    while(top[a]!=top[b]){
        if(dep[top[a]]>dep[top[b]])
            a=fa[top[a]];
        else
            b=fa[top[b]];
    }
    return dep[a]>dep[b]?b:a;
}
ll dis(int a,int b){
	a=idfn[a],b=idfn[b];
    return d[a]+d[b]-2*d[lca(a,b)];
}
void add(int t){
	if(st.empty()){
		ans=0;
		st.insert(t);
		return;
	}
	if(st.size()==1){
		ans=2*dis(*st.begin(),t);
		st.insert(t);
		return;
	}
	st.insert(t);
	int x,y;
	auto it=st.find(t);
	if(it==st.begin())
		x=*--st.end();
	else
		x=*--it;
	it=st.find(t);
	if(it==--st.end())
		y=*st.begin();
	else
		y=*++it;
	ans+=dis(x,t)+dis(t,y)-dis(x,y);
	return;
}
void del(int t){
	if(st.size()<=2){
		st.erase(t);
		ans=0;
		return;
	}
	if(st.size()==3){
		st.erase(t);
		ans=2*dis(*st.begin(),*--st.end());
		return;
	}
	int x,y;
	auto it=st.find(t);
	if(it==st.begin())
		x=*--st.end();
	else
		x=*--it;
	it=st.find(t);
	if(it==--st.end())
		y=*st.begin();
	else
		y=*++it;
	ans-=dis(x,t)+dis(t,y)-dis(x,y);
	st.erase(t);
	return;
}
int main(){
    read(n,m);
    for(int i=1;i<n;i++){
        int x,y,z;
        read(x,y,z);
        e[x].push_back({y,z});
        e[y].push_back({x,z});
    }
    dfs1(1,0);
    dfs2(1,1);
    while(m--){
        int t;
        read(t);
		t=dfn[t];
        if(st.find(t)==st.end())
			add(t);
        else
			del(t);
		printf("%lld\n",ans);
    }
    return 0;
}
