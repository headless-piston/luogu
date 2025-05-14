#include<bits/stdc++.h>
using namespace std;
const int N=3e6+5;
int n,a[N],ans[N];
stack<int> s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(s.empty()||a[i]<=a[s.top()])
			s.push(i);
		else{
			while(!s.empty()&&a[i]>a[s.top()]){
				ans[s.top()]=i;
				s.pop();
			}
			s.push(i);
		}
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
