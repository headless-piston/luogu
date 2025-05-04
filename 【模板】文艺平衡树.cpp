#include<algorithm>
#include<cstdio>
using namespace std;
const int N=1e5+10;
int son[N][2],fa[N],tot,val[N],siz[N],root;
bool tag[N];
bool dir(int x){
	return x==son[fa[x]][1];
}
void push_up(int x){
	siz[x]=1+siz[son[x][0]]+siz[son[x][1]];
}
void update_tag(int x){
	swap(son[x][0],son[x][1]);
	tag[x]^=1;
	return;
}
void push_down(int x){
	if(tag[x]){
		if(son[x][0])
			update_tag(son[x][0]);
		if(son[x][1])
			update_tag(son[x][1]);
		tag[x]=0;
	}
	return;
}
void rotate(int x){
	int y=fa[x],z=fa[y];
	bool r=dir(x);
	son[y][r]=son[x][!r];
	if(son[x][!r])
		fa[son[x][!r]]=y;
	fa[x]=z;
	if(z)
		son[z][dir(y)]=x;
	son[x][!r]=y;
	fa[y]=x;
	push_up(y);
	push_up(x);
	return;
}
void splay(int &z,int x){
	int temp=fa[z];
	while(fa[x]!=temp){
		int y=fa[x];
		if(fa[y]!=temp){
			if(dir(x)==dir(y))
				rotate(y);
			else
				rotate(x);
		}
		rotate(x);
	}
	z=x;
	return;
}
void loc(int &z,int k){
	int x=z;
	push_down(x);
	while(1){
		if(siz[son[x][0]]>=k)
			x=son[x][0];
		else if(siz[son[x][0]]+1>=k)
			break;
		else{
			k-=siz[son[x][0]]+1;
			x=son[x][1];
		}
		push_down(x);
	}
	splay(z,x);
	return;
}
void reverse(int l,int r){
	loc(root,l);//将l转至根节点
	loc(son[root][1],r-l+2);//将r转至根节点的右儿子，由于根已改变，所以第二个参数传的是r-l+2
	int x=son[son[root][1]][0];//根节点右儿子的左儿子，则x为区间(l,r)的根节点
	update_tag(x);
	push_down(x);
	splay(root,x);
	return;
}
void build(int n){//建一条只有左子树的链
	for(int i=0;i<=n+1;i++){
		son[++tot][0]=root;
		if(root)
			fa[root]=tot;
		root=tot;
		val[tot]=i;
		siz[tot]=1;
		push_up(root);
	}
	splay(root,1);
	return;
}
int n;
void dfs(int x){
	if(!x)
		return;
	push_down(x);
	dfs(son[x][0]);
	if(val[x]>=1&&val[x]<=n)
		printf("%d ",val[x]);
	dfs(son[x][1]);
	return;
}
int m,x,y;
int main(){
	scanf("%d%d",&n,&m);
	build(n);
	while(m--){
		scanf("%d%d",&x,&y);
		reverse(x,y);
	}
	dfs(root);
	return 0;
}
