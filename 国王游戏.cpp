#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1010;
int n,a,b;
struct node{
	int a,b;
}e[N];
bool operator<(node x,node y){
	return x.a*x.b<y.a*y.b;
}
struct ll{
	int num[N*5];
	int len;
	ll(){
		memset(num,0,sizeof(num));
		len=0;
		return;
	}
	void operator=(int x){
		while(x){
			num[++len]=x%10;
			x/=10;
		}
		return;
	}
	bool operator<(const ll &x)const{
		if(this->len<x.len)
			return 1;
		if(this->len>x.len)
			return 0;
		for(int i=len;i;i--){
			if(this->num[i]<x.num[i])
				return 1;
			if(this->num[i]>x.num[i])
				return 0;
		}
		return 1;
	}
	ll operator*(const int &x)const{
		ll ans;
		ans.len=this->len;
		for(int i=1;i<=this->len;i++){
			ans.num[i]+=this->num[i]*x;
			ans.num[i+1]=ans.num[i]/10;
			ans.num[i]%=10;
		}
		if(ans.num[ans.len+1]){
			int k=ans.num[ans.len+1];
			while(k){
				ans.len++;
				ans.num[ans.len]=k%10;
				k/=10;
			}
		}
		return ans;
	}
	bool operator<(const int &x)const{
		int k=x,len1=0;
		while(k){
			k/=10;
			len1++;
		}
		if(len1>this->len)
			return 1;
		if(len1<this->len)
			return 0;
		k=x;
		for(int i=1;i<=n;i++){
			if(this->num[i]<k%10)
				return 1;
			if(this->num[i]>k%10)
				return 0;
			k/=10;
		}
		return 0;
	}
	ll operator/(const int &x)const{
		ll ans;
		if(*this<x)
			return ans;
		ans.len=this->len;
		int k=0;
		for(int i=this->len;i;i--){
			k=k*10+this->num[i];
			ans.num[i]=k/x;
			k%=x;
		}
		while(!ans.num[ans.len])
			ans.len--;
		return ans;
	}
};
void print(ll x){
	if(x.len==0){
		printf("0");
		return;
	}
	for(int i=x.len;i;i--)
		printf("%d",x.num[i]);
	return;
}
ll max1(ll x,ll y){
	if(x<y)
		return y;
	return x;
}
ll sum,ans1;
int main(){
	scanf("%d%d%d",&n,&a,&b);
	sum=a;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&e[i].a,&e[i].b);
	sort(e+1,e+1+n);
	for(int i=1;i<=n;i++){
		ans1=max1(ans1,sum/e[i].b);
		sum=sum*e[i].a;
	}
	print(ans1);
	return 0;
}
