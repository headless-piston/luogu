#include<iostream>
#define int long long
using namespace std;
const int MAXN=536870911;
int t,n,k,len,cnt;
long long sum[40],lensum;
long long solve(int u,int l,int r,int x,int y){
	if(x>r||y<l||u<1)
		return 0;
	int len1=(r-l+1-len)/2;
	long long res=0;
	if(y-x+1<=len)
		return (1ll<<k)*(y-x+1);
	if(x<=l&&y>=r)
		return (sum[u]<<k)*len;
	res+=solve(u-1,l,l+len1-1,x,y);
	int l1=max(x,l+len1),r1=min(y,l+len1+len-1);
	res+=max(0ll,(r1-l1+1))*(((1ll<<u)-1)<<k);
	res+=solve(u-1,l+len1+len,r,x,y);
	return res;
}
void get_length(){
	lensum=len;
	while(lensum<=n){
		lensum<<=1;
		lensum+=len;
		cnt++;
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	sum[1]=1;
	for(int i=2;i<=31;i++){
		sum[i]=sum[i-1]<<1;
		sum[i]+=(1ll<<i)-1;
	}
	while(t--){
		cin>>n>>k;
		len=1ll<<k;
		cnt=1;
		get_length();
		cout<<solve(cnt,0,lensum,0,n)<<'\n';
	}
	return 0;
}
