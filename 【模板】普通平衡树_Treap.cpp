#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10,inf=1<<30;
int son[N][2],val[N],rnd[N],siz[N],cnt[N],tot,root;
void push_up(int x){
	siz[x]=cnt[x]+siz[son[x][0]]+siz[son[x][1]];
}
void rotate(int &x,bool dir){
	int temp=son[x][!dir];
	son[x][!dir]=son[temp][dir];
	son[temp][dir]=x;
	x=temp;
	push_up(son[x][dir]);
	push_up(x);
}
void insert(int &x,int v){
	if(!x){
		x=++tot;
		siz[x]=cnt[x]=1;
		val[x]=v;
		rnd[x]=rand();
		return;
	}
	if(val[x]==v)
		cnt[x]++;
	else{
		bool dir=(v>val[x]);
		insert(son[x][dir],v);
		if(rnd[x]<rnd[son[x][dir]])
			rotate(x,!dir);
	}
	push_up(x);
}
void erase(int &x,int v){
	if(!x)
		return;
	if(v<val[x])
		erase(son[x][0],v);
	else if(v>val[x])
		erase(son[x][1],v);
	else{
		if(cnt[x]>1){
			cnt[x]--;
			push_up(x);
			return;
		}
		if(son[x][0]||son[x][1]){
			if(!son[x][1]||rnd[son[x][0]]>rnd[son[x][1]])
				rotate(x,1),erase(son[x][1],v);
			else
				rotate(x,0),erase(son[x][0],v);
			push_up(x);
		}
		else
			x=0;
	}
	push_up(x);
}
int find_rank(int x,int v){
	if(!x)
		return 1;
	if(v==val[x])
		return siz[son[x][0]]+1;
	if(v<val[x])
		return find_rank(son[x][0],v);
	return siz[son[x][0]]+cnt[x]+find_rank(son[x][1],v);
}
int find(int x,int k){
	if(!x)
		return 0;
	if(siz[son[x][0]]>=k)
		return find(son[x][0],k);
	if(siz[son[x][0]]+cnt[x]>=k)
		return val[x];
	return find(son[x][1],k-siz[son[x][0]]-cnt[x]);
}
int find_pre(int v){
	int x=root,pre;
	while(x){
		if(v>val[x])
			pre=val[x],x=son[x][1];
		else
			x=son[x][0];
	}
	return pre;
}
int find_nxt(int v){
	int x=root,nxt;
	while(x){
		if(v<val[x])
			nxt=val[x],x=son[x][0];
		else
			x=son[x][1];
	}
	return nxt;
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
			printf("%d\n",find(root,t));
			break;
		case 5:
			printf("%d\n",find_pre(t));
			break;
		case 6:
			printf("%d\n",find_nxt(t));
			break;
		}
	}
	return 0;
}
