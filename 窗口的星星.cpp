#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1e4+10;
int tree[N*8],tag[N*8],a[N*2],len,w,h,n,x,y,val,t,ans;
struct node{
	int x,l,r,val;
	bool operator<(const node &c)const{
		return this->x<c.x;
	}
}e[N*2];
void push_down(int u,int l,int r){
	int mid=(l+r)/2;
	tree[u*2]+=tag[u],tree[u*2+1]+=tag[u];
	tag[u*2]+=tag[u],tag[u*2+1]+=tag[u],tag[u]=0;
	return;
}
void update(int u,int l,int r,int x,int y,int k){
	if(x>r||y<l)
		return;
	if(x<=l&&y>=r){
		tree[u]+=k;
		tag[u]+=k;
		return;
	}
	push_down(u,l,r);
	int mid=(l+r)/2;
	update(u*2,l,mid,x,y,k);
	update(u*2+1,mid+1,r,x,y,k);
	tree[u]=max(tree[u*2],tree[u*2+1]);
	return;
}
int main(){
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		memset(tag,0,sizeof(tag));
		memset(tree,0,sizeof(tree));
		ans=0;
		scanf("%d%d%d",&n,&w,&h);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&x,&y,&val);
			e[i]=node{x,y,y+h,val},e[i+n]=node{x+w,y,y+h,-val};
			a[i]=y,a[i+n]=y+h;
		}
		sort(e+1,e+1+n*2);
		e[n*2+1].x=-114; 
		sort(a+1,a+1+n*2);
		len=unique(a+1,a+1+n*2)-(a+1);
		for(int i=1;i<=n*2;i++){
			int l=lower_bound(a+1,a+1+len,e[i].l)-a;
			int r=lower_bound(a+1,a+1+len,e[i].r)-a-1;
			update(1,1,len-1,l,r,e[i].val);
			if(e[i].x!=e[i+1].x)
				ans=max(ans,tree[1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
