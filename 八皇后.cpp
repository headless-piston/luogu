#include<iostream>
#include<cstring>
using namespace std;
int n,sum;
const int N=50;
bool a[N],b[N],c[N];
int ans[N];
void print(){
	sum++;
	if(sum<=3){
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
	}
	return;
}
void f(int x){
	if(x==n+1){
		print();
		return;
	}
	for(int i=1;i<=n;i++){
		if(!a[i]&&!b[i+x]&&!c[i-x+n]){
			ans[x]=i;
			a[i]=b[i+x]=c[i-x+n]=1;
			f(x+1);
			a[i]=b[i+x]=c[i-x+n]=0;
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(0),cout.tie(0);
	cin>>n;
	f(1);
	cout<<sum;
	return 0;
}
