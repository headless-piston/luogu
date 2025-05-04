#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500;
const double ex=1e-8;
int n,m;
struct node{
	int c,v;
	double w;
}kc[N];
bool operator<(node a,node b){
	return a.w<b.w;
}
double l,r=1000;
bool check(double x){
	for(int i=1;i<=n;i++)
		kc[i].w=x*kc[i].c-kc[i].v;
	sort(kc+1,kc+1+n);
	double ans=0;
	for(int i=1;i<=m;i++)
		ans+=kc[i].w;
	return ans<=0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&kc[i].v);
	for(int i=1;i<=n;i++)
		scanf("%d",&kc[i].c);
	while(l+ex<=r){
		double mid=(l+r)/2.0;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.3lf",r);
	return 0;
}
