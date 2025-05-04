#include<cstdio>
#include<vector>
#include<string>
#include<iostream>
#include<queue>
using namespace std;
const int N=15,M=2010;
queue<char> pai_dui;
int n,m;
int now=1;//��ǰ����ֻ���ڳ��� 
int cnt;//�غ��� 
int pigs;//����ʣ������ 
int fpigs;//������ 
char pai_d;
bool gameover=0;
bool hui_he_over;
struct pig{
	int shen_fen;//1��ʾ���� 2��ʾ���� 3��ʾ���� 
	int health=4;
	bool dead;
	int tiao;//1��,2�� 
	bool zhuang_bei;
	int bef,nxt;
	vector<char> shou_pai;
}p[N];
bool lei_fan[N];//�෴�� 
//�� P,ɱ K,�� D,���� F,���� N,��� W,��и J,��� Z 
void read(){//Done
	char pai_;
	string shen_f;
	scanf("%d%d",&n,&m);
	pigs=n;
	for(int i=1;i<=n;i++){
		cin>>shen_f;
		if(shen_f=="MP")
			p[i].shen_fen=1;
		else if(shen_f=="ZP")
			p[i].shen_fen=2;
		else
			p[i].shen_fen=3,fpigs++;
		for(int j=1;j<=4;j++){
			cin>>pai_;
			p[i].shou_pai.push_back(pai_);
		}
		p[i].bef=i-1;
		p[i].nxt=i+1;
	}
	p[1].tiao=1;
	p[n].nxt=1;
	p[1].bef=n;
	while(m--){
		cin>>pai_d;
		pai_dui.push(pai_d);
	}
}//Done
void tao(int place){//Done
	if(gameover)
		return;
	auto it=p[place].shou_pai.begin();
	while(it!=p[place].shou_pai.end()&&p[place].health<4){
		if(*it=='P'){
			p[place].health++;
			p[place].shou_pai.erase(it);
		}
		else
			it++;
	}
	return;
}//Done
void mo_pai(int place,int num){
	if(gameover)
		return;
	for(int i=1;i<=num;i++){
		p[place].shou_pai.push_back(pai_dui.front());
		pai_dui.pop();
		if(pai_dui.empty()){
			pai_dui.push(pai_d);
		}//�������ݻ��ò��� 
	}
	return;
}//done
bool wu_xie1(int place){//
	if(gameover)
		return 0;
	if(p[place].tiao==1){
		int place1=place;
		bool huan=1;
		while(place1!=place||huan){
			huan=0;
			if(p[place1].shen_fen==3){
				auto it=p[place1].shou_pai.begin();
				while(it!=p[place1].shou_pai.end()){
					if(*it=='J'){
						p[place1].shou_pai.erase(it);
						p[place1].tiao=2;
						lei_fan[place1]=0;
						return !wu_xie1(place1);
					}
					it++;
				}
			}
			place1=p[place1].nxt;
		}
	}
	else if(p[place].tiao==2){
		int place1=place;
		bool huan=1;
		while(place1!=place||huan){
			huan=0;
			if(p[place1].shen_fen==1||p[place1].shen_fen==2){
				auto it=p[place1].shou_pai.begin();
				while(it!=p[place1].shou_pai.end()){
					if(*it=='J'){
						p[place1].shou_pai.erase(it);
						p[place1].tiao=1;
						lei_fan[place1]=0;
						return !wu_xie1(place1);
					}
					it++;
				}
			}
			place1=p[place1].nxt;
		}
	}
	return 0;
}
bool wu_xie(int place){//����������Ҳ������и������ 
	//��һ����и 
	if(gameover)
		return 0;
	if(p[place].tiao==0)
		return 0;
	if(p[place].tiao==1){
		bool huan=1;
		int place1=now;
		while(place1!=now||huan){
			huan=0;
			if(p[place1].shen_fen==1||p[place1].shen_fen==2){
				auto it=p[place1].shou_pai.begin();
				while(it!=p[place1].shou_pai.end()){
					if(*it=='J'){
						p[place1].shou_pai.erase(it);
						p[place1].tiao=1;
						lei_fan[place1]=0;
						return !wu_xie1(place1);
					}
					else
						it++;
				}
			}
			place1=p[place1].nxt;
		}
	}
	else{
		bool huan=1;
		int place1=now;
		while(place1!=now||huan){
			huan=0;
			if(p[place1].shen_fen==3){
				auto it=p[place1].shou_pai.begin();
				while(it!=p[place1].shou_pai.end()){
					if(*it=='J'){
						p[place1].shou_pai.erase(it);
						p[place1].tiao=2;
						lei_fan[place1]=0;
						return !wu_xie1(place1);
					}
					else
						it++;
				}
			}
			place1=p[place1].nxt;
		}
	}
	return 0;
}
bool bin_si(int place,int lai_yuan){//������/�˺���Դ Done 
	auto it=p[place].shou_pai.begin();
	while(it!=p[place].shou_pai.end()){
		if(*it=='P'){
			p[place].health++;
			p[place].shou_pai.erase(it);
			return 0;
		}
		else
			it++;
	}//�Ƿ����� 
	if(p[place].shen_fen==1){//�������� 
		p[place].dead=1;
		printf("FP\n");
		for(int i=1;i<n;i++){
			if(p[i].dead)
				printf("DEAD");
			else if(p[i].shou_pai.size()){
				auto it=p[i].shou_pai.begin();
				printf("%c",*it),it++;
				while(it!=p[i].shou_pai.end())
					printf(" %c",*it),it++;
			}
			printf("\n");
		}
		if(p[n].dead)
				printf("DEAD");
		else if(p[n].shou_pai.size()){
			auto it=p[n].shou_pai.begin();
			printf("%c",*it),it++;
			while(it!=p[n].shou_pai.end())
				printf(" %c",*it),it++;
		}
		exit(0);
		gameover=1;
		return 1;
	}
	else{
		p[place].dead=1;
		p[p[place].bef].nxt=p[place].nxt;
		p[p[place].nxt].bef=p[place].bef;
		if(p[place].shen_fen==3){
			fpigs--;
			if(fpigs==0){//����ȫ������ 
				printf("MP\n");
				for(int i=1;i<n;i++){
					if(p[i].dead)
						printf("DEAD");
					else if(p[i].shou_pai.size()){
						auto it=p[i].shou_pai.begin();
						printf("%c",*it),it++;
						while(it!=p[i].shou_pai.end())
							printf(" %c",*it),it++;
					}
					printf("\n");
				}
				if(p[n].dead)
						printf("DEAD");
				else if(p[n].shou_pai.size()){
					auto it=p[n].shou_pai.begin();
					printf("%c",*it),it++;
					while(it!=p[n].shou_pai.end())
						printf(" %c",*it),it++;
				}
				exit(0);
				gameover=1;
				return 1;
			}
			mo_pai(lai_yuan,3);//����3�ƽ��� 
		}
		else if(p[place].shen_fen==2&&p[lai_yuan].shen_fen==1){
			p[lai_yuan].shou_pai.clear();
			p[lai_yuan].zhuang_bei=0;
			hui_he_over=1;
		}//�������Ƴͷ� 
	}
	return 0;
}
void nan_wan(int place,char need){
	if(gameover)
		return;
	int place1=p[place].nxt;
	while(place1!=place){
		bool xiang_ying=0;
		if(p[place1].tiao)
			if(wu_xie(place1)){
				place1=p[place1].nxt;
				xiang_ying=1;
				continue;
			}
		auto it=p[place1].shou_pai.begin();
		while(it!=p[place1].shou_pai.end()){
			if(*it==need){
				p[place1].shou_pai.erase(it);
				place1=p[place1].nxt;
				xiang_ying=1;
				break;
			}
			it++;
		}
		if(!xiang_ying){
			p[place1].health--;
			if(p[place1].shen_fen==1)
				lei_fan[place]=1;
			if(p[place1].health<1)
				if(bin_si(place1,place))
					return;
			place1=p[place1].nxt;
		}
	}
	return;
}
void jue_dou1(int place,int place1,int cnt1){//˫����������������ɱ 
	if(gameover)
		return;
	int cnt2=0;//������ ������ ������ɱ���� 
	auto it2=p[place1].shou_pai.begin();
	while(it2!=p[place1].shou_pai.end()){
		if(*it2=='K')
			cnt2++;
		it2++;
	}//������ɱ���� 
	if(cnt1>=cnt2){//������ʤ�� 
		cnt1-=cnt2;//������ʣ���ɱ 
		auto it3=p[place1].shou_pai.begin();
		while(it3!=p[place1].shou_pai.end()){
			if(*it3=='K')
				p[place1].shou_pai.erase(it3);
			else
				it3++;
		}//���ʧ���ߵ�ɱ 
		it3=p[place].shou_pai.begin();
		while(it3!=p[place].shou_pai.end()){
			if(*it3=='K'){
				if(cnt1==0)
					p[place].shou_pai.erase(it3);
				else cnt1--,it3++;
			}
			else it3++;
		}//���ɹ��ߵ�ɱ 
		p[place1].health--;
		if(p[place1].health<1)
			if(bin_si(place1,place))
				return;
	}
	else{//������ʧ�� 
		cnt2-=cnt1;//ʤ����ʣ��ɱ 
		cnt2--;//������1 
		auto it3=p[place].shou_pai.begin();
		while(it3!=p[place].shou_pai.end()){
			if(*it3=='K')
				p[place].shou_pai.erase(it3);
			else
				it3++;
		}//��շ����ߵ�ɱ 
		it3=p[place1].shou_pai.begin();
		while(it3!=p[place1].shou_pai.end()){
			if(*it3=='K'){
				if(cnt2==0)
					p[place1].shou_pai.erase(it3);
				else cnt2--,it3++;
			}
			else it3++;
		}//��ʤ���ߵ�ɱ 
		p[place].health--;
		if(p[place].health<1)
			bin_si(place,place1);
		if(p[place].dead)
			hui_he_over=1;
	}
	return;
}
bool jue_dou(int place,vector<char>::iterator itk){//������
	if(gameover)
		return 0;
	bool used=0;
	int cnt1=0;//������ɱ������
	auto it1=p[place].shou_pai.begin();
	while(it1!=p[place].shou_pai.end()){
		if(*it1=='K')
			cnt1++;
		it1++;
	}
	if(p[place].shen_fen==1){//������ 
		int place1=p[place].nxt;
		while(place1!=place){//�ҵ�һ�������� 
			if(p[place1].tiao==2||(lei_fan[place1]&&p[place1].shen_fen==3)){//�Է�����෴���� 
				used=1;
				p[place].shou_pai.erase(itk);//ʹ�� 
				if(wu_xie(place1))
					return used;
				jue_dou1(place,place1,cnt1);
				return used;
			}
			else if(lei_fan[place1]&&p[place1].shen_fen==2){//���෴���� 
				used=1;
				p[place].shou_pai.erase(itk);
				bool xiang_ying=0;
				if(!wu_xie(place1)){
					p[place1].health--;
					if(p[place1].health<1){
						bin_si(place1,place);
					}
					return used;
				}
				if(!xiang_ying){//δ��Ӧ 
					p[place1].health--;
					if(p[place1].health<1){
						bin_si(place1,place);
					}
					return used;
				}
			}
			else place1=p[place1].nxt;
		}
	}
	else if(p[place].shen_fen==2){//������ 
		int place1=p[place].nxt;
		while(place1!=place){
			if(p[place1].tiao==2){//Ŀ������ 
				p[place].tiao=1;
				lei_fan[place]=0;//���� 
				used=1;
				p[place].shou_pai.erase(itk);
				if(wu_xie(place1))
					return used;
				jue_dou1(place,place1,cnt1);
				return used;
			}
			place1=p[place1].nxt;
		}
	}
	else{//������ 
		p[place].tiao=2;//����ֻ�ܶ�������� 
		lei_fan[place]=0;
		used=1;
		p[place].shou_pai.erase(itk);
		if(wu_xie(1))
			return used;
		jue_dou1(place,1,cnt1);
		return used;
	}
	return 0;
}
bool shan(int place){//0 ���ܳɹ�,1 ����ʧ��
	if(gameover)
		return 1;
	auto it=p[place].shou_pai.begin();
	while(it!=p[place].shou_pai.end()){
		if(*it=='D'){
			p[place].shou_pai.erase(it);
			return 0;
		}
		it++;
	}
	return 1;
}
bool sha(int place,vector<char>::iterator it){
	if(gameover)
		return 0;
	bool used=0;
	int place1=p[place].nxt;
	if(p[place].shen_fen==1){//���� 
		if(p[place1].tiao==2||lei_fan[place1]){//�������෴ 
			used=1;
			p[place].shou_pai.erase(it);
			if(shan(place1)){
				p[place1].health--;
				if(p[place1].health<1){
					if(bin_si(place1,place))
						return used;
				}
			}
		}
	}
	else if(p[place].shen_fen==2){//���� 
		if(p[place1].tiao==2){//���� 
			p[place].tiao=1;
			lei_fan[place]=0;
			used=1;
			p[place].shou_pai.erase(it);
			if(shan(place1)){
				p[place1].health--;
				if(p[place1].health<1){
					if(bin_si(place1,place))
						return used;
				}
			}
		}
	}
	else{//���� 
		if(p[place1].tiao==1){//���� 
			p[place].tiao=2;
			lei_fan[place]=0;
			used=1;
			p[place].shou_pai.erase(it);
			if(shan(place1)){
				p[place1].health--;
				lei_fan[place]=0;
				if(p[place1].health<1){
					if(bin_si(place1,place))
						return used;
				}
			}
		}
	}
	return used;
}
void chu_pai(int place){
	if(gameover)
		return;
	bool able_sha=1;
	hui_he_over=0;
	auto itk=p[place].shou_pai.begin();
	while(p[place].shou_pai.size()&&itk!=p[place].shou_pai.end()&&!gameover&&!hui_he_over){
		switch(*itk){
			case 'Z':{//������� 
				p[place].shou_pai.erase(itk);
				p[place].zhuang_bei=1;
				itk=p[place].shou_pai.begin();
				able_sha=1;
				break;
			}
			case 'K':{//ɱ 
				if(able_sha&&sha(place,itk)){
					able_sha=0;
					itk=p[place].shou_pai.begin();
				}
				else
					itk++;
				if(p[place].zhuang_bei)
					able_sha=1;
				break;
			}
			case 'F':{//���� 
				if(jue_dou(place,itk))
					itk=p[place].shou_pai.begin();
				else
					itk++;
				break;
			}
			case 'W':{//��� 
				p[place].shou_pai.erase(itk);
				nan_wan(place,'D');
				if(p[place].shou_pai.size())
					itk=p[place].shou_pai.begin();
				break;
			}
			case 'N':{//���� 
				p[place].shou_pai.erase(itk);
				nan_wan(place,'K');
				if(p[place].shou_pai.size())
					itk=p[place].shou_pai.begin();
				break;
			}
			case 'P':{//�� 
				if(p[place].health<4){
					p[place].health++;
					p[place].shou_pai.erase(itk);
				}
				else
					itk++;
				break;
			}
			default:{
				itk++;
				break;
			}
		}
	}
	return;
}
int main(){
	read();
	while(!gameover){
		if(now==1)
			cnt++;
		mo_pai(now,2);
		chu_pai(now);
		now=p[now].nxt;
	}
	return 0;
}
