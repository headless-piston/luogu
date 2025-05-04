#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1e6+10;
int n,q,a[N],l[N],r[N],block,tot,belong[N],b[N],tag[N];
void reset(int x){
	for(int i=l[x];i<=r[x];i++)
		b[i]=a[i];
	sort(b+l[x],b+r[x]+1);
	return;
}
void modify(int x,int y,int k){
	if(belong[x]==belong[y]){//x，y在同一块内
		for(int i=x;i<=y;i++)
			a[i]+=k;
		reset(belong[x]);
		return;
	}
	for(int i=x;i<=r[belong[x]];i++)
		a[i]+=k;//暴力修改左侧超出的部分
	reset(belong[x]);
	for(int i=l[belong[y]];i<=y;i++)
		a[i]+=k;//右侧
	reset(belong[y]);
	for(int i=belong[x]+1;i<belong[y];i++)
		tag[i]+=k;//无需特判最后一块是因为最后一块一定会被暴力修改
	return;
}
int query(int x,int y,int k){
	int res=0;
	if(belong[x]==belong[y]){
		for(int i=x;i<=y;i++)
			res+=a[i]+tag[belong[x]]>=k;
		return res;
	}
	for(int i=x;i<=r[belong[x]];i++)
		res+=a[i]+tag[belong[x]]>=k;
	for(int i=l[belong[y]];i<=y;i++)
		res+=a[i]+tag[belong[y]]>=k;
	for(int i=belong[x]+1;i<belong[y];i++){
		int pos=lower_bound(b+l[i],b+r[i]+1,k-tag[i])-b;
		res+=r[i]-pos+1;
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	block=sqrt(n);
	tot=n/block;
	if(n%block)
		tot++;
	for(int i=1;i<=n;i++)
		belong[i]=(i-1)/block+1;
	for(int i=1;i<=tot;i++){
		l[i]=(i-1)*block+1;
		r[i]=min(i*block,n);
		sort(b+l[i],b+r[i]+1);
	}
	char opt;
	int x,y,k;
	while(q--){
		scanf(" %c%d%d%d",&opt,&x,&y,&k);
		if(opt=='M')
			modify(x,y,k);
		else
			printf("%d\n",query(x,y,k));
	}
	return 0;
}
