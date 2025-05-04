#include<iostream>
#define ls u<<1
#define rs u<<1|1
using namespace std;
const int N=2e5+10;
int tot,n,m,maxlen,a[N];
struct Tree{
	long long sum,tag;
	int len;
}tree[(1<<22)+10];
void push_up(int u){
	tree[u].sum=tree[ls].sum+tree[rs].sum;
	tree[u].len=tree[ls].len+tree[rs].len;
	return;
}
void build(int u,int l,int x){
	if(l==maxlen){
		if(x>=1&&x<=n){
			tree[u].sum=a[x];
			tree[u].len=1;
		}
		return;
	}
	build(ls,l+1,x);
	build(rs,l+1,1<<l|x);
	push_up(u);
	return;
}
void push_down(int u){
	tree[ls].sum+=tree[u].tag*tree[ls].len;
	tree[ls].tag+=tree[u].tag;
	tree[rs].sum+=tree[u].tag*tree[rs].len;
	tree[rs].tag+=tree[u].tag;
	tree[u].tag=0;
	return;
}
void modify(int u,int l,int len,int x,long long k){
	if(l==len){
		tree[u].sum+=k*tree[u].len;
		tree[u].tag+=k;
		return;
	}
	push_down(u);
	if(x>>l&1)
		modify(rs,l+1,len,x,k);
	else
		modify(ls,l+1,len,x,k);
	push_up(u);
	return;
}
long long query(int u,int l,int len,int x){
	if(l==len)
		return tree[u].sum;
	push_down(u);
	if(x>>l&1)
		return query(rs,l+1,len,x);
	else
		return query(ls,l+1,len,x);
}
int op,x,y,v;
long long lastans;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	maxlen=20;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(1,0,0);
	while(m--){
		cin>>op;
		op=(lastans+op)%2+1;
		if(op==1){
			cin>>x>>y>>v;
			modify(1,0,x,y,v);
		}
		else{
			cin>>x>>y;
			lastans=query(1,0,x,y);
			cout<<lastans<<'\n';
		}
	}
	return 0;
}
