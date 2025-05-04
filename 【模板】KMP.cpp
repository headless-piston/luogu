#include<cstdio>
#include<cstring>
const int N=1e6+10;
char s1[N],s2[N];
int len1,len2,nxt[N];
int main(){
	scanf("%s%s",s1+1,s2+1);
	len1=strlen(s1+1),len2=strlen(s2+1);
	int j=0;
	for(int i=2;i<=len2;i++){
		while(j&&s2[j+1]!=s2[i])
			j=nxt[j];
		if(s2[j+1]==s2[i])
			j++;
		nxt[i]=j;
	}
	j=0;
	for(int i=1;i<=len1;i++){
		while(j&&s2[j+1]!=s1[i])
			j=nxt[j];
		if(s2[j+1]==s1[i])
			j++;
		if(j==len2){
			printf("%d\n",i-j+1);
			j=nxt[j];
		}
	}
	for(int i=1;i<=len2;i++)
		printf("%d ",nxt[i]);
	return 0;
}
