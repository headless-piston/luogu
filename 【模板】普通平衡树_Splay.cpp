#include<cstdio>
const int N=1e5+10;
int son[N][2],fa[N],tot,val[N],cnt[N],siz[N],root;
bool dir(int x){
	return x==son[fa[x]][1];
}
void push_up(int x){
	siz[x]=cnt[x]+siz[son[x][0]]+siz[son[x][1]];
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
void find(int &z,int v){
	int x=z,y=fa[x];
	while(x&&val[x]!=v){
		y=x;
		if(v<val[x])
			x=son[x][0];
		else
			x=son[x][1];
	}
	splay(z,x?x:y);
	return;
}
void loc(int &z,int k){
	int x=z;
	while(1){
		if(siz[son[x][0]]>=k)
			x=son[x][0];
		else if(siz[son[x][0]]+cnt[x]>=k)
			break;
		else{
			k-=siz[son[x][0]]+cnt[x];
			x=son[x][1];
		}
	}
	splay(z,x);
	return;
}
int merge(int x,int y){
	if(!x||!y)
		return x|y;
	loc(y,1);
	son[y][0]=x;
	fa[x]=y;
	push_up(y);
	return y;
}
void insert(int &z,int v){
	int x=z,y=0;
	while(x&&val[x]!=v){
		y=x;
		if(v<val[x])
			x=son[x][0];
		else
			x=son[x][1];
	}
	if(x)
		cnt[x]++,siz[x]++;
	else{
		x=++tot;
		val[x]=v;
		cnt[x]=siz[x]=1;
		fa[x]=y;
		if(y){
			if(v<val[y])
				son[y][0]=x;
			else
				son[y][1]=x;
		}
	}
	splay(z,x);
	return;
}
bool erase(int &z,int v){
	find(z,v);
	if(!z||val[z]!=v)
		return 0;
	cnt[z]--,siz[z]--;
	if(!cnt[z]){
		int x=son[z][0],y=son[z][1];
		fa[x]=fa[y]=0;
		z=merge(x,y);
	}
	return 1;
}
int find_rank(int &z,int v){
	find(z,v);
	int res=siz[son[z][0]]+1;
	if(val[z]<v)
		res+=cnt[z];
	return res;
}
int find_pre(int &z,int v){
	find(z,v);
	if(z&&val[z]<v)
		return val[z];
	int x=son[z][0];
	if(!x)
		return -1;
	while(son[x][1])
		x=son[x][1];
	splay(z,x);
	return val[z];
}
int find_nxt(int &z,int v){
	find(z,v);
	if(z&&val[z]>v)
		return val[z];
	int x=son[z][1];
	if(!x)
		return -1;
	while(son[x][0])
		x=son[x][0];
	splay(z,x);
	return val[z];
}
int n,opt,t;
int main(){
	scanf("%d",&n);
	while(n--){
		scanf("%d%d",&opt,&t);
		switch(opt){
		case 1:
			insert(root,t);
			break;
		case 2:
			erase(root,t);
			break;
		case 3:
			printf("%d\n",find_rank(root,t));
			break;
		case 4:
			loc(root,t);
			printf("%d\n",val[root]);
			break;
		case 5:
			printf("%d\n",find_pre(root,t));
			break;
		default:
			printf("%d\n",find_nxt(root,t));
			break;
		}
	}
	return 0;
}
