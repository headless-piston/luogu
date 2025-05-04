#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
struct FHQ_Treap{
	int ls,rs;
	int val,rnd,siz;
}t[N];
int root,tot;
void push_up(int u){
	t[u].siz=t[t[u].ls].siz+t[t[u].rs].siz+1;
}
int build(int val){
	t[++tot].rnd=rand()<<15|rand();
	t[tot].siz=1;
	t[tot].val=val;
	return tot;
}
void split(int p,int val,int &lrt,int &rrt){
	if(!p){
		lrt=rrt=0;
		return;
	}
	if(t[p].val<=val){
		lrt=p;
		split(t[p].rs,val,t[p].rs,rrt);
	}
	else{
		rrt=p;
		split(t[p].ls,val,lrt,t[p].ls);
	}
	push_up(p);
	return;
}
int merge(int l,int r){
	if(!l||!r)
		return l|r;
	if(t[l].rnd>t[r].rnd){
		t[l].rs=merge(t[l].rs,r);
		push_up(l);
		return l;
	}
	else{
		t[r].ls=merge(l,t[r].ls);
		push_up(r);
		return r;
	}
}
void insert(int val){
	int x,y;
	split(root,val,x,y);
	root=merge(merge(x,build(val)),y);
	return;
}
void erase(int val){
	int x,y,temp;
	split(root,val,x,y);
	split(x,val-1,x,temp);
	temp=merge(t[temp].ls,t[temp].rs);
	root=merge(merge(x,temp),y);
	return;
}
int find_rank(int val){
	int x,y;
	split(root,val-1,x,y);
	int res=t[x].siz+1;
	root=merge(x,y);
	return res;
}
int find_kth(int k){
	int p=root;
	while(1){
		if(t[t[p].ls].siz+1==k)
			break;
		else if(t[t[p].ls].siz+1>k)
			p=t[p].ls;
		else
			k-=t[t[p].ls].siz+1,p=t[p].rs;
	}
	return t[p].val;
}
int pre(int val){
	int x,y;
	split(root,val-1,x,y);
	int p=x;
	while(t[p].rs)
		p=t[p].rs;
	root=merge(x,y);
	return t[p].val;
}
int nxt(int val){
	int x,y;
	split(root,val,x,y);
	int p=y;
	while(t[p].ls)
		p=t[p].ls;
	root=merge(x,y);
	return t[p].val;
}
int n,opt,x;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&opt,&x);
		switch(opt){
		case 1:
			insert(x);
			break;
		case 2:
			erase(x);
			break;
		case 3:
			printf("%d\n",find_rank(x));
			break;
		case 4:
			printf("%d\n",find_kth(x));
			break;
		case 5:
			printf("%d\n",pre(x));
			break;
		default:
			printf("%d\n",nxt(x));
			break;
		}
	}
	return 0;
}
