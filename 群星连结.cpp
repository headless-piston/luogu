#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int n,alice=0,bob=0,t=0;
int addmp_[24000][2];
int addatk_[24000][2];//���� id 6 7
int adddef_[24000][2];//���� id 8 9
int over10,over10m=-1;//�������غ��� ��������10��Ӫ
struct juese{
	int HP,hp;
	bool die;
	int MP,mp;
	int atk,datk;
	int def,ddef;
	int A(){return max(atk+datk,1);}
	int D(){return max(def+ddef,0);}
	int tf,tfx,tfy;
	int jn,jnx,jny,jnz;
	queue<int> attack;
}js[11][2];//0ΪAlice 1ΪBob
void read1(bool m){
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&js[i][m].HP,&js[i][m].MP,&js[i][m].atk,&js[i][m].def);
		js[i][m].hp=js[i][m].HP;
		int p;
		for(int j=1;j<=n;j++){
			scanf("%d",&p);
			js[i][m].attack.push(p);
		}
		scanf("%d%d%d",&js[i][m].tf,&js[i][m].tfx,&js[i][m].tfy);
		scanf("%d%d%d%d",&js[i][m].jn,&js[i][m].jnx,&js[i][m].jny,&js[i][m].jnz);
	}
	return;
}
void read(){
	scanf("%d",&n);
	read1(0);
	read1(1);
	return;
}//done
void over(){
	if(alice==n){//bobʤ
		printf("%d\nBob\n",t);
		for(int i=1;i<=n;i++)
			printf("%d ",js[i][1].hp);
	}
	else{//aliceʤ
		printf("%d\nAlice\n",t);
		for(int i=1;i<=n;i++)
			printf("%d ",js[i][0].hp);
	}
	exit(0);
}//done
void addhp(int j,bool m,int x){//��ɫ���� ��Ӫ ������
	js[j][m].hp=min(js[j][m].hp+x,js[j][m].HP);
	return;
}//done
void addmp(int j,bool m,int x){
	js[j][m].mp=min(js[j][m].mp+x,js[j][m].MP);
	return;
}//done
int attack_sum(int x,bool m,int d,int r){//���������� ��������Ӫ �˺� ��ʵ�˺� 
	if(js[x][m].tf==1)//�츳Ѫ��Ƥ������һ����ʵ�˺� 
		return max(d-js[x][m].D(),0)+r-r/2;
	else
		return max(d-js[x][m].D(),0)+r;
}
void reduce_hp(int x,bool m,int d,int r){//���������� ��������Ӫ �˺� ��ʵ�˺� 
	addmp(x,m,1);//��������ֵ�۳����ں������������ 1 
	js[x][m].hp-=attack_sum(x,m,d,r);//Ѫ���۳� 
	if(js[x][m].hp<=0){//���� 
		js[x][m].die=1;
		js[x][m].hp=0;
		for(int i=1;i<=n;i++)//���µз���ɫ�Ĺ���Ŀ�� 
			while(js[js[i][!m].attack.front()][m].die)//���Ŀ����������һֱ���� 
				js[i][!m].attack.pop();
		if(m)//������������
			bob++;
		else
			alice++;
	}
	if(alice==n||bob==n)//һ����ɫȫ��������Ϸ���� 
		over();
	return;
}
void j0(){return;}
void j1(int j,bool m){//������ ��������Ӫ id 1
	for(int i=1;i<=n;i++)
		if(!js[i][!m].die){//�з�Ŀ��û��
			reduce_hp(i,!m,js[j][m].jnx,0);
			addmp(i,!m,-js[i][!m].mp/10);
		}
}//done
void j2(int j,bool m){//id 2
	for(int i=1;i<=n;i++)
		if(!js[i][!m].die)
			reduce_hp(i,!m,0,js[j][m].A());
	return;
}//done
void j3(int j,bool m){//id 3
	for(int i=1;i<=n;i++)
		if(!js[i][!m].die)
			reduce_hp(i,!m,min(js[i][!m].HP/10,js[j][m].jnx*js[j][m].A()),0);
	return;
}//done
void j4(int j,bool m){//id 4
	for(int i=t;i<=min(23350,t+js[j][m].jnx-1);i++)
		addmp_[i][m]+=js[j][m].jny;//�����ж�����ʱ��
	return;
}//done
void j5(int j,bool m){//id 5
	js[js[j][m].attack.front()][!m].ddef-=js[j][m].jnx;
	reduce_hp(js[j][m].attack.front(),!m,0,js[j][m].A());
	return;
}//done
void j6(int j,bool m){//id 6
	reduce_hp(js[j][m].attack.front(),!m,0,js[j][m].A());
	for(int i=1;i<=n;i++)
		if(!js[i][!m].die)
			js[i][!m].datk-=js[j][m].jny;
	addatk_[min(23350,t+js[j][m].jnx-1)][!m]+=js[j][m].jny;//�غϽ����ڼ�ż� 
	return;
}//done
void j7(int j,bool m){//id 7
	int minm=1,minhp=1e9+10;//Ѫ����ͽ�ɫ��� ���Ѫ��
	for(int i=1;i<=n;i++)
		if(!js[i][m].die&&js[i][m].hp<minhp)//С�ںű�֤�����С
			minm=i,minhp=js[i][m].hp;//�Ҽ���Ѫ����͵Ľ�ɫ
	addhp(minm,m,js[j][m].jnz);
	for(int i=1;i<=n;i++)
		if(!js[i][m].die)
			js[i][m].datk+=js[j][m].jny;
	addatk_[min(23350,t+js[j][m].jnx-1)][m]-=js[j][m].jny;//�غϽ���
	return;
}//done
void j8(int j,bool m){//id 8
	for(int i=1;i<=n;i++)
		if(!js[i][!m].die)
			reduce_hp(i,!m,js[j][m].A(),0);
	for(int i=1;i<=n;i++)
		if(!js[i][!m].die)
			js[i][!m].ddef-=js[j][m].jny;
	adddef_[min(23350,t+js[j][m].jnx-1)][!m]+=js[j][m].jny;
	return;
}//done
void j9(int j,bool m){//id 9
	for(int i=1;i<=n;i++)
		if(!js[i][m].die){
			addhp(i,m,js[j][m].jnz);
			js[i][m].ddef+=js[j][m].jny;
		}
	adddef_[min(23350,t+js[j][m].jnx-1)][m]-=js[j][m].jny;
	return;
}//done
void j10(int j,bool m){//id 10
	for(int i=1;i<=n;i++){
		if(!js[i][m].die){
			js[i][m].def*=2;
			js[i][m].atk*=2;
			js[i][m].hp=max(js[i][m].HP/2,js[i][m].hp);
			js[i][m].mp=max(js[i][m].MP/2,js[i][m].mp);
		}
	}
	for(int i=t;i<=min(23350,t+js[j][m].jnx-1);i++)
		addmp_[i][m]++;
	over10=min(23350,t+js[j][m].jnx-1);
	over10m=m;
	for(int i=1;i<=n;i++){//������ 
		if(js[i][0].jn==10)
			js[i][0].jn=0;
		if(js[i][1].jn==10)
			js[i][1].jn=0;
	}
	return;
}//done
void jn(int j,bool m){
	if(js[j][m].die)
		return;
	js[j][m].mp=0;//�������
	switch(js[j][m].jn){
		case 0:{j0();break;}
		case 1:{j1(j,m);break;}
		case 2:{j2(j,m);break;}
		case 3:{j3(j,m);break;}
		case 4:{j4(j,m);break;}
		case 5:{j5(j,m);break;}
		case 6:{j6(j,m);break;}
		case 7:{j7(j,m);break;}
		case 8:{j8(j,m);break;}
		case 9:{j9(j,m);break;}
		default:{j10(j,m);break;}
	}
	addmp(j,m,1);//�������ܺ����� 1����
	if(js[j][m].tf==5)//�츳�Ƽ����� 
		addmp(j,m,js[j][m].tfy);
	return;
}//done
void movement(bool m){
	int mx=0;//������
	for(int i=1;i<=n;i++)
		if(!js[i][m].die&&js[i][m].mp==js[i][m].MP)//�ɷ�������
			if(js[i][m].jn>=js[mx][m].jn)//���ܱ��
				mx=i;
	if(mx!=0)
		jn(mx,m);
	else{//��ͨ����
		int maxatk=0,maxhp=0,attacker=0;//���������˺� ����Ŀ�����Ѫ��
		for(int i=1;i<=n;i++)
			if(!js[i][m].die&&js[js[i][m].attack.front()][!m].hp>maxhp)
				maxhp=js[js[i][m].attack.front()][!m].hp;//������Ŀ���е����Ѫ��
		for(int i=1;i<=n;i++){
			if(js[i][m].die)
				continue;
			if(js[js[i][m].attack.front()][!m].hp==maxhp){
				int common_atk=0;
				if(js[i][m].tf==4)//�츳 ������ʥ 
					common_atk=attack_sum(js[i][m].attack.front(),!m,0,js[i][m].A());
				else if(js[i][m].tf==2)//�츳 �Ǻ�����Ͷ�� 
					common_atk=attack_sum(js[i][m].attack.front(),!m,js[i][m].A(),js[i][m].tfx);
				else
					common_atk=attack_sum(js[i][m].attack.front(),!m,js[i][m].A(),0);
				maxatk=max(common_atk,maxatk);//�ҿɿ۳�����ֵ�����ֵ
			}
		}
		for(int i=1;i<=n;i++){
			if(js[i][m].die)
				continue;
			if(js[js[i][m].attack.front()][!m].hp==maxhp){
				int common_atk;
				if(js[i][m].tf==4)
					common_atk=attack_sum(js[i][m].attack.front(),!m,0,js[i][m].A());
				else if(js[i][m].tf==2)
					common_atk=attack_sum(js[i][m].attack.front(),!m,js[i][m].A(),js[i][m].tfx);
				else
					common_atk=attack_sum(js[i][m].attack.front(),!m,js[i][m].A(),0);
				if(common_atk==maxatk)
					attacker=i;
			}
		}//�ҵ���
		if(js[attacker][m].tf==4)
			reduce_hp(js[attacker][m].attack.front(),!m,0,js[attacker][m].A());
		else if(js[attacker][m].tf==2)
			reduce_hp(js[attacker][m].attack.front(),!m,js[attacker][m].A(),js[attacker][m].tfx);
		else
			reduce_hp(js[attacker][m].attack.front(),!m,js[attacker][m].A(),0);
		addmp(attacker,m,1);
		if(js[attacker][m].tf==5)
			addhp(attacker,m,js[attacker][m].tfx);
	}
	for(int i=1;i<=n;i++){ 
		if(js[i][m].die)
			continue;
		if(js[i][m].tf==3){//�츳 ��ʤ����
			addhp(i,m,js[i][m].tfx);
			addmp(i,m,js[i][m].tfy);
		}
		addmp(i,m,addmp_[t][m]);
		addmp(i,m,1);
	}
	return;
}
void work(){
	while(++t<=23333){
		movement(0);
		movement(1);
		for(int i=1;i<=n;i++){//�����漰�����������������ľ��ڻغϽ���ʱ���� 
			if(!js[i][0].die){
				js[i][0].datk+=addatk_[t][0];
				js[i][0].ddef+=adddef_[t][0];
			}
			if(!js[i][1].die){
				js[i][1].datk+=addatk_[t][1];
				js[i][1].ddef+=adddef_[t][1];
			}
		}
		if(t==over10){
			if(over10m==1)
				bob=n;
			else
				alice=n;
			over();
		}
	}
	printf("QwQ");
	return;
}
int main(){
	read();
	work();
	return 0;
}
