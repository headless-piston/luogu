#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
double const eps=1e-9;
int n,a[N],b[N],c[N],t;
double l,r,mid1,mid2;
double fun(double x,int i){
	return a[i]*x*x+b[i]*x+c[i];
}
double check(double x){
	double ans=INT_MIN;
	for(int i=1;i<=n;i++)
		ans=max(ans,fun(x,i));
	return ans;
}
int main(){
	scanf("%d",&t);
	while(t--){
		l=0,r=1000;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d%d",&a[i],&b[i],&c[i]);
		while(l+eps<r){
			mid1=l+(r-l)/3.0,mid2=r-(r-l)/3.0;
			if(check(mid1)>check(mid2))
				l=mid1;
			else
				r=mid2;
		}
		printf("%.4lf\n",check(l));
	}
	return 0;
}
