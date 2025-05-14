#include<cstdio>
#define lowbit(x) x&-x
const int N=2050;
int n,m,a,b,c,d,delta,ans;
char opt;
struct BIT{
	int Tree[N][N];
	void modify(int x,int y,int k){
		for(int i=x;i<=n;i+=lowbit(i))
			for(int j=y;j<=m;j+=lowbit(j))
				Tree[i][j]+=k;
		return;
	}
	int query(int x,int y){
		int res=0;
		for(int i=x;i;i-=lowbit(i))
			for(int j=y;j;j-=lowbit(j))
				res+=Tree[i][j];
		return res;
	}
}tree1,tree2,tree3,tree4;
void modify(int x,int y,int k){
	tree1.modify(x,y,k);
	tree2.modify(x,y,k*(x-1));
	tree3.modify(x,y,k*(y-1));
	tree4.modify(x,y,k*(x-1)*(y-1));
	return;
}
int query(int x,int y){
	int res=0;
	res+=tree1.query(x,y)*x*y;
	res-=tree2.query(x,y)*y;
	res-=tree3.query(x,y)*x;
	res+=tree4.query(x,y);
	return res;
}
int main(){
	scanf("X %d%d",&n,&m);
	while(scanf(" %c %d%d%d%d",&opt,&a,&b,&c,&d)!=EOF){
		if(opt=='L'){
			scanf("%d",&delta);
			modify(a,b,delta);
			modify(c+1,d+1,delta);
			modify(a,d+1,-delta);
			modify(c+1,b,-delta);
		}
		else{
			ans=0;
			ans+=query(c,d);
			ans+=query(a-1,b-1);
			ans-=query(a-1,d);
			ans-=query(c,b-1);
			printf("%d\n",ans);
		}
	}
	return 0;
}
