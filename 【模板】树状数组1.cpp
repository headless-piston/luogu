#include<cstdio>
using namespace std;
const int N=5e5+10;
int n,m,a[N],tree[N],c,x,y,k;
int lowbit(int x){
	return x&-x;
}
void build(){
	for(int i=1;i<=n;i++)
		for(int j=i-lowbit(i)+1;j<=i;j++)
			tree[i]+=a[j];
	return;
}
void add(int x,int num){
	a[x]+=num;
	for(int i=x;i<=n;i+=lowbit(i))
		tree[i]+=num;
	return;
}
int ask(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=tree[i];
	return sum;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build();
	for(int i=1;i<=m;i++){
		scanf("%d",&c);
		if(c==1){
			scanf("%d%d",&x,&k);
			add(x,k);
		}
		else{
			scanf("%d%d",&x,&y);
			printf("%d\n",ask(y)-ask(x-1));
		}
	}
	return 0;
}
