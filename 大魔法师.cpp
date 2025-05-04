#include<iostream>
#include<cstring>
#define mod 998244353
#define ls u*2
#define rs u*2+1
using namespace std;
const int N=2.5e5+10;
int n,m;
struct Matrix{
	int x[5][5];
	Matrix(){
		memset(x,0,sizeof(x));
		return;
	}
	void base(){
		memset(x,0,sizeof(x));
		for(int i=1;i<=4;i++)
			x[i][i]=1;
		return;
	}
	Matrix operator*(const Matrix &a)const{
		Matrix res;
		for(int k=1;k<=4;k++)
			for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
					res.x[i][j]=(res.x[i][j]+1ll*x[i][k]*a.x[k][j])%mod;
		return res;
	}
	Matrix operator+(const Matrix &a)const{
		Matrix res;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				res.x[i][j]=(x[i][j]+a.x[i][j])%mod;
		return res;
	}
}a[N],b[10];
Matrix tree[N*4],tag[N*4];
void push_up(int u){
	tree[u]=tree[ls]+tree[rs];
	return;
}
void build(int u,int l,int r){
	tag[u].base();
	if(l==r){
		tree[u]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(u);
	return;
}
void push_down(int u){
	tree[ls]=tree[ls]*tag[u],tree[rs]=tree[rs]*tag[u];
	tag[ls]=tag[ls]*tag[u],tag[rs]=tag[rs]*tag[u];
	tag[u].base();
	return;
}
void modify(int u,int l,int r,int x,int y,const Matrix &p){
	if(x<=l&&y>=r){
		tree[u]=tree[u]*p;
		tag[u]=tag[u]*p;
		return;
	}
	push_down(u);
	int mid=(l+r)/2;
	if(x<=mid)
		modify(ls,l,mid,x,y,p);
	if(y>mid)
		modify(rs,mid+1,r,x,y,p);
	push_up(u);
	return;
}
Matrix query(int u,int l,int r,int x,int y){
	if(x<=l&&y>=r)
		return tree[u];
	Matrix res;
	push_down(u);
	int mid=(l+r)/2;
	if(x<=mid)
		res=res+query(ls,l,mid,x,y);
	if(y>mid)
		res=res+query(rs,mid+1,r,x,y);
	return res;
}
void init(){
	b[1].base();
	b[1].x[2][1]=1;
	b[2].base();
	b[2].x[3][2]=1;
	b[3].base();
	b[3].x[1][3]=1;
	b[4].base();
	b[5].base();
	b[6].base();
	b[6].x[3][3]=0;
	return;
}
int opt,l,r,v;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	init();
	for(int i=1;i<=n;i++){
		cin>>a[i].x[1][1]>>a[i].x[1][2]>>a[i].x[1][3];
		a[i].x[1][4]=1;
	}
	build(1,1,n);
	cin>>m;
	while(m--){
		cin>>opt>>l>>r;
		if(opt>=4&&opt<=6)
			cin>>v;
		if(opt==1)
			modify(1,1,n,l,r,b[1]);
		else if(opt==2)
			modify(1,1,n,l,r,b[2]);
		else if(opt==3)
			modify(1,1,n,l,r,b[3]);
		else if(opt==4){
			b[4].x[4][1]=v;
			modify(1,1,n,l,r,b[4]);
		}
		else if(opt==5){
			b[5].x[2][2]=v;
			modify(1,1,n,l,r,b[5]);
		}
		else if(opt==6){
			b[6].x[4][3]=v;
			modify(1,1,n,l,r,b[6]);
		}
		else{
			Matrix res=query(1,1,n,l,r);
			cout<<res.x[1][1]<<' '<<res.x[1][2]<<' '<<res.x[1][3]<<'\n';
		}
	}
	return 0;
}
