#include<cstdio>
#include<algorithm>
#define lowbit(x) x&-x
#define inf 2147483647
using namespace std;
const int N=5e4+10;
int n,m,a[N],tot,len,cnt1,cnt2;
struct Tree{
	int val,ls,rs;
}t[N*100];
struct Query{
	int opt,l,r,k,pos;
}q[N];
int root[N],b[N*2],temp1[N],temp2[N];
void push_up(int u){
	t[u].val=t[t[u].ls].val+t[t[u].rs].val;
}
void modify1(int &u,int l,int r,int x,int v){
	if(!u)
		u=++tot;
	if(l==r){
		t[u].val+=v;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
		modify1(t[u].ls,l,mid,x,v);
	else
		modify1(t[u].rs,mid+1,r,x,v);
	push_up(u);
	return;
}
void modify(int u,int v){
	for(int i=u;i<=n;i+=lowbit(i))
		modify1(root[i],1,len,a[u],v);
}
int query(int l,int r,int k){
	if(l==r)
		return l;
	int mid=(l+r)/2,sum=0;
	for(int i=1;i<=cnt1;i++)
		sum+=t[t[temp1[i]].ls].val;
	for(int i=1;i<=cnt2;i++)
		sum-=t[t[temp2[i]].ls].val;
	if(k<=sum){
		for(int i=1;i<=cnt1;i++)
			temp1[i]=t[temp1[i]].ls;
		for(int i=1;i<=cnt2;i++)
			temp2[i]=t[temp2[i]].ls;
		return query(l,mid,k);
	}
	else{
		for(int i=1;i<=cnt1;i++)
			temp1[i]=t[temp1[i]].rs;
		for(int i=1;i<=cnt2;i++)
			temp2[i]=t[temp2[i]].rs;
		return query(mid+1,r,k-sum);
	}
}
int find_num(int l,int r,int k){
	cnt1=cnt2=0;
	for(int i=r;i;i-=lowbit(i))
		temp1[++cnt1]=root[i];
	for(int i=l-1;i;i-=lowbit(i))
		temp2[++cnt2]=root[i];
	return query(1,len,k);
}
int query_rank(int l,int r,int k){
	if(l==r)
		return 0;
	int mid=(l+r)/2,sum=0;
	if(k<=mid){
		for(int i=1;i<=cnt1;i++)
			temp1[i]=t[temp1[i]].ls;
		for(int i=1;i<=cnt2;i++)
			temp2[i]=t[temp2[i]].ls;
		return query_rank(l,mid,k);
	}
	else{
		for(int i=1;i<=cnt1;i++){
			sum+=t[t[temp1[i]].ls].val;
			temp1[i]=t[temp1[i]].rs;
		}
		for(int i=1;i<=cnt2;i++){
			sum-=t[t[temp2[i]].ls].val;
			temp2[i]=t[temp2[i]].rs;
		}
		return sum+=query_rank(mid+1,r,k);
	}
}
int find_rank(int l,int r,int k){
	cnt1=cnt2=0;
	for(int i=r;i;i-=lowbit(i))
		temp1[++cnt1]=root[i];
	for(int i=l-1;i;i-=lowbit(i))
		temp2[++cnt2]=root[i];
	return query_rank(1,len,k)+1;
}
int find_pre(int l,int r,int k){
	int rk=find_rank(l,r,k)-1;
	if(rk==0)
		return 0;
	return find_num(l,r,rk);
}
int find_nxt(int l,int r,int k){
	if(k==len)
		return len+1;
	int rk=find_rank(l,r,k+1);
	if(rk==r-l+2)
		return len+1;
	return find_num(l,r,rk);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[++len]=a[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&q[i].opt);
		if(q[i].opt==3){
			scanf("%d%d",&q[i].pos,&q[i].k);
			b[++len]=q[i].k;
		}
		else
			scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
		if(q[i].opt==4||q[i].opt==5)
			b[++len]=q[i].k;
	}
	sort(b+1,b+1+len);
	len=unique(b+1,b+1+len)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+1+len,a[i])-b;
		modify(i,1);
	}
	b[0]=-inf,b[len+1]=inf;
	for(int i=1;i<=m;i++){
		if(q[i].opt==1){
			q[i].k=lower_bound(b+1,b+1+len,q[i].k)-b;
			printf("%d\n",find_rank(q[i].l,q[i].r,q[i].k));
		}
		else if(q[i].opt==2)
			printf("%d\n",b[find_num(q[i].l,q[i].r,q[i].k)]);
		else if(q[i].opt==3){
			modify(q[i].pos,-1);
			a[q[i].pos]=lower_bound(b+1,b+1+len,q[i].k)-b;
			modify(q[i].pos,1);
		}
		else if(q[i].opt==4){
			q[i].k=lower_bound(b+1,b+1+len,q[i].k)-b;
			printf("%d\n",b[find_pre(q[i].l,q[i].r,q[i].k)]);
		}
		else if(q[i].opt==5){
			q[i].k=lower_bound(b+1,b+1+len,q[i].k)-b;
			printf("%d\n",b[find_nxt(q[i].l,q[i].r,q[i].k)]);
		}
	}
	return 0;
}
