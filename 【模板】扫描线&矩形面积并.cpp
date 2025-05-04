#include<cstdio>
#include<algorithm>
#define ll long long
#define y1 AC
#define y2 WA
using namespace std;
const int N=1e5+10;
int a[N*2],len,n;
ll tree_sum[N*8],tree_len[N*8],ans;
struct node{
	int x,l,r,val;
	bool operator<(const node &a)const{
		return this->x<a.x;
	}
}e[N*2];
void push_up(int u,int l,int r){
	if(tree_sum[u])
		tree_len[u]=a[r]-a[l];
	else if(l+1==r)
		tree_len[u]=0;
	else
		tree_len[u]=tree_len[u*2]+tree_len[u*2+1];
	return;
}
void add(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree_sum[u]+=k;
		push_up(u,l,r);
		return;
	}
	int mid=(l+r)/2;
	if(l+1==r)
		return;
	add(u*2,l,mid,x,y,k);
	add(u*2+1,mid,r,x,y,k);
	push_up(u,l,r);
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		e[i*2-1]=node{x1,y1,y2,1};
		e[i*2]=node{x2,y1,y2,-1};
		a[i*2-1]=y1,a[i*2]=y2;
	}
	sort(a+1,a+1+n*2);
	sort(e+1,e+1+n*2);
	len=unique(a+1,a+1+n*2)-(a+1);
	for(int i=1;i<=n*2;i++){
		ans+=tree_len[1]*(e[i].x-e[i-1].x);
		int l=lower_bound(a+1,a+1+len,e[i].l)-a;
		int r=lower_bound(a+1,a+1+len,e[i].r)-a;
		add(1,1,len,l,r,e[i].val);
	}
	printf("%lld",ans);
	return 0;
}
