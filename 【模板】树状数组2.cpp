#include<cstdio>
using namespace std;
const int N=500010;
int n,m,a[N],tree[N],c,x,y,k;
int lowbit(int x){
	return x&-x;
}
void add(int x,int num){
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
	for(int i=1;i<=m;i++){
		scanf("%d",&c);
		if(c==1){
			scanf("%d%d%d",&x,&y,&k);
			add(x,k);
			add(y+1,-k);
		}
		else{
			scanf("%d",&x);
			printf("%d\n",a[x]+ask(x));
		}
	}
	return 0;
}
