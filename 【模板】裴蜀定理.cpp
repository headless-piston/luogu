#include<cstdio>
int gcd(int m,int n){
	while(n!=0){
		int t=m%n;
		m=n;
		n=t;
	}
	return m;
}
int n,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a;
		scanf("%d",&a);
		if(a<0)
			a=-a;
		ans=gcd(ans,a);
	}
	printf("%d",ans);
	return 0;
}
