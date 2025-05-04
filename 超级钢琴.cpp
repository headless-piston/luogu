#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int N=5e5+10;
int n,k,l,r,a,sum[N],st[N][35],place[N][35];
long long ans;
void build(){
	for(int j=1;j<=__lg(n);j++)
		for(int i=1;i+(1<<j)-1<=n;i++){
			if(st[i][j-1]>st[i+(1<<(j-1))][j-1]){
				st[i][j]=st[i][j-1];
				place[i][j]=place[i][j-1];
			}
			else{
				st[i][j]=st[i+(1<<(j-1))][j-1];
				place[i][j]=place[i+(1<<(j-1))][j-1];
			}
		}
	return;
}
int stmax(int l,int r){//返回最大值所在位置 
	int len=__lg(r-l+1);
	if(st[l][len]>st[r-(1<<len)+1][len])
		return place[l][len];
	else
		return place[r-(1<<len)+1][len];
}
struct node{
	int s,l,r,t;
};
bool operator<(node u,node v){
	return sum[u.t]-sum[u.s-1]<sum[v.t]-sum[v.s-1];
}
priority_queue<node> q;
int main(){
	scanf("%d%d%d%d",&n,&k,&l,&r);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		sum[i]=a+sum[i-1];
		st[i][0]=sum[i];
		place[i][0]=i;
	}
	build();
	for(int i=1;i+l-1<=n;i++){
		int l1=i+l-1,r1=min(n,i+r-1);
		q.push({i,l1,r1,stmax(l1,r1)});
	}
	for(int i=1;i<=k;i++){
		node u=q.top();
		q.pop();
		ans+=sum[u.t]-sum[u.s-1];
		if(u.t>u.l){
			int l1=u.l,r1=u.t-1;
			q.push({u.s,l1,r1,stmax(l1,r1)});
		}
		if(u.t<u.r){
			int l1=u.t+1,r1=u.r;
			q.push({u.s,l1,r1,stmax(l1,r1)});
		}//由当前最优解到处可能的次优解 
	}
	printf("%lld",ans);
	return 0;
}
