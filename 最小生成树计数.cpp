#include<cstdio>
#include<algorithm>
#define mod 31011
using namespace std;
const int N=1010;
int n,m,fa[N],cnt[N],tot,color[N],num,sum;
long long ans=1;
struct edge{
	int u,v,w;
}e[N];
struct node{
	int l,r;
}g[N];
int find(int x){
	if(fa[x]!=x)
		return find(fa[x]);
	return x;
}
bool operator<(edge a,edge b){
	return a.w<b.w;
}
void dfs(int x,int now,int sum){
	if(now>g[x].r){
		if(sum==cnt[x])
			tot++;
		return;
	}
	int u=find(e[now].u),v=find(e[now].v);
	if(u!=v){
		fa[u]=v;
		dfs(x,now+1,sum+1);
		fa[u]=u;
	}
	dfs(x,now+1,sum);
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+1+m);
	for(int i=1;i<=m+1;i++){
		if(e[i].w!=e[i-1].w){
			g[num].r=i-1;
			g[++num].l=i;
		}
		color[i]=num;
	}
	for(int i=1;i<=m;i++){
		int u=find(e[i].u),v=find(e[i].v);
		if(u==v)
			continue;
		fa[u]=v;
		sum+=e[i].w;
		tot++;
		cnt[color[i]]++;
	}
	if(tot<n-1){
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<num;i++){
		tot=0;
		dfs(i,g[i].l,0);
		ans=ans*tot%mod;
		for(int j=g[i].l;j<=g[i].r;j++){
			int u=find(e[j].u),v=find(e[j].v);
			if(u!=v)
				fa[u]=v;
		}
	}
	printf("%lld",ans);
	return 0;
}
