#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,k,a[N];
int qmx[N],qmn[N],l1=1,l2=1,r1,r2,ma[N],mi[N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		while(l2<=r2&&qmn[l2]<i-k+1)
			qmn[l2++]=0;
		while(l2<=r2&&a[i]<a[qmn[r2]])
			qmn[r2--]=0;
		qmn[++r2]=i;
		while(l1<=r1&&qmx[l1]<i-k+1)
			qmx[l1++]=0;
		while(l1<=r1&&a[i]>a[qmx[r1]])
			qmx[r1--]=0;
		qmx[++r1]=i;
		if(i-k+1>=1)
			mi[i-k+1]=qmn[l2],ma[i-k+1]=qmx[l1];
	}
	for(int i=1;i<=n-k+1;i++)
		printf("%d ",a[mi[i]]);
	printf("\n");
	for(int i=1;i<=n-k+1;i++)
		printf("%d ",a[ma[i]]);
	return 0;
}
