#include<cstdio>
#include<stack>
using namespace std;
const int N=1e7+10;
int n,p[N],son[N][2],st[N],top;
long long ans1,ans2;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	for(int i=1;i<=n;i++){
		int last=0;
		while(top&&p[st[top]]>p[i])
			last=st[top--];
		if(top)
			son[st[top]][1]=i;
		son[i][0]=last;
		st[++top]=i;
	}
	for(int i=1;i<=n;i++){
		ans1^=1ll*i*(son[i][0]+1);
		ans2^=1ll*i*(son[i][1]+1);
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
}
