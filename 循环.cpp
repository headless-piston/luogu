#include<cstdio>
#include<cstring>
#include<cassert>
#include<cmath>
const int N=1145;
int k;
struct ll{
	int num[N];
	ll(){
		memset(num,0,sizeof(num));
		return;
	}
	void read(){
		char s[N];
		memset(s,0,sizeof(s));
		scanf("%s",s);
		int len=strlen(s);
		for(int i=0;i<len;i++)
			num[len-i]=s[i]-'0';
		return;
	}
	void write(){
		int len=200;
		while(!num[len])
			len--;
		for(int i=len;i;i--)
			printf("%d",num[i]);
		return;
	}
	ll operator*(const ll &x)const{
		ll res;
		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++){
				res.num[i+j-1]+=num[i]*x.num[j];
				res.num[i+j]+=res.num[i+j-1]/10;
				res.num[i+j-1]%=10;
			}
		for(int i=k+1;i<=200;i++)
			res.num[i]=0;
		return res;
	}
	void operator*=(const ll &x){
		*this=*this*x;
		return;
	}
	ll operator*(const int &x){
		ll res;
		for(int i=1;i<=k;i++){
			res.num[i]+=num[i]*x;
			res.num[i+1]=res.num[i]/10;
			res.num[i]%=10;
		}
		for(int i=k+1;i<=200;i++)
			num[i]=0;
		return res;
	}
	void operator*=(const int &x){
		*this=*this*x;
		return;
	}
}n,mul,ans;
int main(){
	ans.num[1]=1;
	n.read();
	scanf("%d",&k);
	mul=n;
	for(int i=1;i<=k;i++){
		bool flag=1;
		ll tmp=n;
		for(int j=1;j<=10;j++){
			tmp*=mul;
			if(tmp.num[i]==n.num[i]){
				flag=0;
				ans*=j;
				tmp=mul;
				for(int k1=1;k1<j;k1++)
					mul*=tmp;
				break;
			}
		}
		if(flag){
			printf("-1");
			return 0;
		}
	}
	ans.write();
	return 0;
}
