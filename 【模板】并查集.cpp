#include<cstdio>
using namespace std;
const int N=2e5+10;
int n,m,father[N],x,y,z;
int find(int x){
	if(father[x]==x) return x;
	return father[x]=find(father[x]);
}
void merge(int a,int b){
	a=find(a);
	b=find(b);
	father[a]=b;
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		father[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&z,&x,&y);
		if(z==1)
			merge(x,y);
		else{
			if(find(x)==find(y))
				printf("Y\n");
			else
				printf("N\n");
		}
	}
	return 0;
}
