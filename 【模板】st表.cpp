#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
int n,m,a[N],st[N][20],l,r;
void build(){
	for(int j=1;j<=__lg(n);j++)
		for(int i=1;i+(1<<j)<=n+1;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&st[i][0]);
	build();
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		int k=__lg(r-l+1);
		printf("%d\n",max(st[l][k],st[r-(1<<k)+1][k]));
	}
	return 0;
}
