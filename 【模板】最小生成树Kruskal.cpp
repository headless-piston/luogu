#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5010,M=2e5+10;
int father[N],n,m,tot,ans;
struct edge{
	int u,v,w;
}e[M];
int find(int x){
	if(father[x]!=x)
		return father[x]=find(father[x]);
	return x;
}
bool operator<(edge a,edge b){
	return a.w<b.w;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		father[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+1+m);
	for(int i=1;i<=m;i++){
		int x=find(e[i].u),y=find(e[i].v);
		if(x==y)
			continue;
		father[x]=y;
		ans+=e[i].w;
		if(++tot==n-1)
			break;
	}
	if(tot!=n-1)
		printf("orz");
	else
		printf("%d",ans);
	return 0;
}
