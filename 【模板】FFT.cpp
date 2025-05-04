#include<cstdio>
#include<cmath>
using namespace std;
const int N=1<<22;
const double PI=acos(-1);
int n,m,a[N],b[N],len=1;
struct comp{
	double real,imag;
}fa[N],fb[N],fc[N];
comp operator+(const comp &x,const comp &y){
	return comp{x.real+y.real,x.imag+y.imag};
}
comp operator-(const comp &x,const comp &y){
	return comp{x.real-y.real,x.imag-y.imag};
}
comp operator*(const comp &x,const comp &y){
	return comp{x.real*y.real-x.imag*y.imag,x.real*y.imag+y.real*x.imag};
}
comp operator/(const comp &x,const int &y){
	return comp{x.real/(double)y,x.imag/(double)y};
}
void FFT(comp *f,int n,int rev){
	for(int i=1,j=n>>1,k;i<n-1;i++){
		if(i<j)
			swap(f[i],f[j]);
		k=n>>1;
		while(j>=k){
			j-=k;
			k>>=1;
		}
		j+=k;
	}
	for(int len=2;len<=n;len<<=1){
		double arg=2*PI*rev/len;
		comp wn={cos(arg),sin(arg)};
		for(int i=0;i<n;i+=len){
			comp w={1,0};
			for(int j=0;j<len/2;j++){
				comp f1=f[i+j];
				comp f2=f[i+j+len/2];
				f[i+j]=f1+w*f2;
				f[i+j+len/2]=f1-w*f2;
				w=w*wn;
			}
		}
	}
	if(!~rev)
		for(int i=0;i<n;i++)
			f[i]=f[i]/n;
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
		scanf("%d",a+i);
	for(int i=0;i<=m;i++)
		scanf("%d",b+i);
	while(len<=n+m)
		len<<=1;
	for(int i=0;i<=n;i++)
		fa[i]={(double)a[i],0};
	for(int i=0;i<=m;i++)
		fb[i]={(double)b[i],0};
	FFT(fa,len,1);
	FFT(fb,len,1);
	for(int i=0;i<len;i++)
		fc[i]=fa[i]*fb[i];
	FFT(fc,len,-1);
	for(int i=0;i<=n+m;i++)
		printf("%d ",(int)round(fc[i].real));
	return 0;
}
