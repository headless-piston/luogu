#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2.2e7+10;
char s[N],a[N];
int p[N];//表示以每个点为中心的回文串半径
int c;//当前最右回文中心
int r;//当前最右回文边界
int n,len,ans;
int main(){
	scanf("%s",a);
	s[0]=s[len=1]='#';
	for(int i=0;a[i]!='\0';i++){
		s[++len]=a[i];
		s[++len]='#';
	}
	for(int i=1;i<len;i++){
		if(r>i)
			p[i]=min(r-i,p[2*c-i]);
		else
			p[i]=1;
		while(s[i+p[i]]==s[i-p[i]])
			p[i]++;
		if(p[i]+i>r){
			r=p[i]+i;
			c=i;
			ans=max(ans,p[i]);
		}
	}
	printf("%d",ans-1);
	return 0;
}
