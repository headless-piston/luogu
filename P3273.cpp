#include<iostream>
#include<queue>
using namespace std;
constexpr int N=3e5+10;
struct node{
    int val,id;
    node(int val,int id):val(val),id(id){}
    bool operator<(const node &x)const{return val==x.val?id<x.id:val<x.val;}
    bool operator==(const node &x)const{return val==x.val&&id==x.id;}
    node operator+(const int &x)const{return node(val+x,id);}
};
int n,a[N],fa[N],Q,tag[N],stag;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct heap{
    priority_queue<node> val,del;
    inline void erase(const node &x){del.push(x);}
    inline node top(){
        while(!del.empty()&&val.top()==del.top()) val.pop(),del.pop();
        return val.top();
    }
    inline void push(const node &x){val.push(x);}
    inline void pop(){
        while(!del.empty()&&val.top()==del.top()) val.pop(),del.pop();
        val.pop();
    }
    inline int size(){return val.size()-del.size();}
}q[N],s;
string op;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        fa[i]=i;
        q[i].push(node(a[i],i));
        s.push(node(a[i],i));
    }
    cin>>Q;
    int x,y,v;
    while(Q--){
        cin>>op;
        if(op=="U"){
            cin>>x>>y;
            x=find(x),y=find(y);
            if(x==y) continue;
            if(q[x].size()>q[y].size()) swap(x,y);
            fa[x]=y;
            s.erase(q[x].top()+tag[x]);
            s.erase(q[y].top()+tag[y]);
            int temp=tag[x]-tag[y];
            while(q[x].size()){
                a[q[x].top().id]+=temp;
                q[y].push(q[x].top()+temp);
                q[x].pop();
            }
            s.push(q[y].top()+tag[y]);
        }
        else if(op=="A1"){
            cin>>x>>v;
            int id=x;
            x=find(x);
            s.erase(q[x].top()+tag[x]);
            q[x].erase(node(a[id],id));
            a[id]+=v;
            q[x].push(node(a[id],id));
            s.push(q[x].top()+tag[x]);
        }
        else if(op=="A2"){
            cin>>x>>v;
            x=find(x);
            s.erase(q[x].top()+tag[x]);
            tag[x]+=v;
            s.push(q[x].top()+tag[x]);
        }
        else if(op=="A3"){
            cin>>v;
            stag+=v;
        }
        else if(op=="F1"){
            cin>>x;
            int id=x;
            x=find(x);
            cout<<a[id]+tag[x]+stag<<'\n';
        }
        else if(op=="F2"){
            cin>>x;
            x=find(x);
            cout<<q[x].top().val+tag[x]+stag<<'\n';
        }
        else cout<<s.top().val+stag<<'\n';
    }
    return 0;
}
