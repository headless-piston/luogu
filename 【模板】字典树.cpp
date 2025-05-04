#include<cstdio>
#include<cstring>
const int N=3e6+10;
int id(char c){
	if(c>='A'&&c<='Z')
		return c-'A';
	else if(c>='a'&&c<='z')
		return c-'a'+26;
	else
		return c-'0'+52;
}
struct trie{
	int nxt[N][65],tot,cnt[N];
	void init(){
		for(int i=0;i<=tot;i++)
			for(int j=0;j<=64;j++)
				nxt[i][j]=0;
		for(int i=0;i<=tot;i++)
			cnt[i]=0;
		tot=0;
		return;
	}
	void insert(char s[]){
		int p=0,len=strlen(s);
		for(int i=0;i<len;i++){
			int c=id(s[i]);
			if(!nxt[p][c])
				nxt[p][c]=++tot;
			p=nxt[p][c];
			cnt[p]++;
		}
	}
	int find(char s[]){
		int p=0,len=strlen(s);
		for(int i=0;i<len;i++){
			int c=id(s[i]);
			if(!nxt[p][c])
				return 0;
			p=nxt[p][c];
		}
		return cnt[p];
	}
};
int t,n,q;
char s[N];
trie a;
int main(){
	scanf("%d",&t);
	while(t--){
		a.init();
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			a.insert(s);
		}
		for(int i=1;i<=q;i++){
			scanf("%s",s);
			printf("%d\n",a.find(s));
		}
	}
	return 0;
}
