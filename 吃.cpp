#include<cstdio>
#include<algorithm>
#define mod 1000000007
using namespace std;
const int N=5e5+10;
int n,idx;
long long res=1;
struct node{
	int a,b;
}food[N];
bool cmp1(node x,node y){
	return x.a<y.a;
}
bool cmp2(node x,node y){
	return x.a*(res+y.b)<y.a*(res+x.b);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&food[i].a);
	for(int i=1;i<=n;i++)
		scanf("%d",&food[i].b);
	sort(food+1,food+1+n,cmp1);
	for(int i=1;i<=n;i++){
		if(food[i].a!=1){
			idx=i;
			break;
		}
		else
			res+=food[i].b;
	}
	if(idx==0){
		printf("%lld",res%mod);
		return 0;
	}
	sort(food+idx,food+n+1,cmp2);
	if(res*food[idx].a>res+food[idx].b)
		res=(res*food[idx].a)%mod;
	else
		res=(res+food[idx].b)%mod;
	for(int i=idx+1;i<=n;i++)
		res=(res*food[i].a)%mod;
	printf("%lld",res);
	return 0;
}
