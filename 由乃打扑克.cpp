#include<iostream>
#include<algorithm>
#include<cmath>
#define inf 2e9
using namespace std;
const int N=1e5+10;
int n,m,a[N],b[N],L[N],R[N],tot,block,belong[N],tag[N];
void build(){
	block=sqrt(n);
	tot=n/block;
	if(n%block)
		tot++;
	for(int i=1;i<=n;i++)
		belong[i]=(i-1)/block+1;
	for(int i=1;i<=tot;i++){
		L[i]=(i-1)*block+1;
		R[i]=min(i*block,n);
		sort(b+L[i],b+R[i]+1);
	}
	return;
}
void reset(int x){
	for(int i=L[x];i<=R[x];i++)
		b[i]=a[i];
	sort(b+L[x],b+R[x]+1);
	return;
}
void modify(int l,int r,int k){
	int x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++)
			a[i]+=k;
		reset(x);
		return;
	}
	for(int i=l;i<=R[x];i++)
		a[i]+=k;
	reset(x);
	for(int i=L[y];i<=r;i++)
		a[i]+=k;
	reset(y);
	for(int i=x+1;i<y;i++)
		tag[i]+=k;
	return;
}
int find_min(int l,int r){
	int res=inf,x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++)
			res=min(res,a[i]+tag[x]);
		return res;
	}
	for(int i=l;i<=R[x];i++)
		res=min(res,a[i]+tag[x]);
	for(int i=L[y];i<=r;i++)
		res=min(res,a[i]+tag[y]);
	for(int i=x+1;i<y;i++)
		res=min(res,b[L[i]]+tag[i]);
	return res;
}
int find_max(int l,int r){
	int res=-inf,x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++)
			res=max(res,a[i]+tag[x]);
		return res;
	}
	for(int i=l;i<=R[x];i++)
		res=max(res,a[i]+tag[x]);
	for(int i=L[y];i<=r;i++)
		res=max(res,a[i]+tag[y]);
	for(int i=x+1;i<y;i++)
		res=max(res,b[R[i]]+tag[i]);
	return res;
}
int check(int l,int r,int k){
	int res=0,x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++)
			if(a[i]+tag[x]<=k)
				res++;
		return res;
	}
	for(int i=l;i<=R[x];i++)
		if(a[i]+tag[x]<=k)
			res++;
	for(int i=L[y];i<=r;i++)
		if(a[i]+tag[y]<=k)
			res++;
	for(int i=x+1;i<y;i++){
		if(b[L[i]]+tag[i]>k)
			continue;
		if(b[R[i]]+tag[i]<=k){
			res+=block;
			continue;
		}
		int pos=upper_bound(b+L[i],b+R[i]+1,k-tag[i])-b;
		res+=pos-L[i];
	}
	return res;
}
int query(int l,int r,int k){
	if(l<1||r-l+1<k)
		return -1;
	int x=find_min(l,r),y=find_max(l,r);
	while(x<=y){
		int mid=(1ll*x+y)/2;
		if(check(l,r,mid)<k)
			x=mid+1;
		else
			y=mid-1;
	}
	return x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	build();
	int opt,l,r,k;
	while(m--){
		cin>>opt>>l>>r>>k;
		if(opt==1)
			cout<<query(l,r,k)<<'\n';
		else
			modify(l,r,k);
	}
	return 0;
}
