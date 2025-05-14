#include<cstdio>
#include<algorithm>
#define lowbit(x) x&-x
using namespace std;
const int N=1e6+10;
int tree[N],n,m,a[N],now,vis[N],ans[N];
struct node{
	int l,r,id;
}ask[N];
bool cmp(node x,node y){
	return x.r<y.r;
}
void modify(int x,int k){
	for(;x<=n;x+=lowbit(x))
		tree[x]+=k;
	return;
}
int query(int x){
	int res=0;
	for(;x;x-=lowbit(x))
		res+=tree[x];
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m,cmp);
	now=1;
	for(int i=1;i<=m;i++){
		for(int j=now;j<=ask[i].r;j++){
			if(vis[a[j]])
				modify(vis[a[j]],-1);
			modify(j,1);
			vis[a[j]]=j;
		}
		now=ask[i].r+1;
		ans[ask[i].id]=query(ask[i].r)-query(ask[i].l-1);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
