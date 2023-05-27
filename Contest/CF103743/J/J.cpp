#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}
 
const int M=2e6+5;
int er[200],s[200];
int Sum=0;
void Geter(int x,int y,int cntx,int cnty){
//	cout<<"now"<<x<<" "<<y<<' '<<cntx<<" "<<cnty<<"@ "<<Sum<<endl;
	if(x<=2&&y<=2) return;
	int xx,yy,cx=0,cy=0;
	if(x&1) Sum+=cntx;
	if(y&1) Sum+=cnty;
	if(x&1){
		xx=x/2;yy=x/2+1;
		cx++;cy++;
		if(x==y){
			cx++;cy++;
		}
		else{
			if(xx==y/2) cx+=2;
			else cy+=2;
		}
	}
	else{
		xx=x/2;cx+=2;
		if(x==y){
			cx+=2;
		}
		else{
			if(y/2==xx) yy=y/2+1;
			else yy=y/2;
			cx++;cy++;
		}
	}
	Geter(xx,yy,cx*cntx,cy*cnty);
	return;
}
 
int ksm(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;y>>=1;
	}
	return ans;
}
 
int Getcnt(int x,int y){
	/*if(y==1) return x;
	int ans=0;
	if(y&1){
		ans=2*(Getcnt(x/2,y/2)*Getcnt(x/2,y/2+1));
	}
	else{
		ans=Getcnt(x/2,y/2);
		ans=ans*ans;
	}
	return ans;*/
	
	int mi=0;Sum=0;
	while(er[mi]*y<=x) mi++;
	mi--;
	int cnt1=(x-y*er[mi])/er[mi];
	int cnt2=y-cnt1;
	int cnt3;
	if(y&1){
		if(y!=1) Sum++;
		Geter(y/2,y/2+1,1,1);
	}
	else Geter(y/2,y/2,1,1);
	cnt3=Sum;
	//cout<<cnt1<<" "<<cnt2<<" "<<cnt3<<endl;
	int ans=ksm(er[mi],cnt2)*ksm(er[mi+1],cnt1)*er[cnt3];
	return ans;
	
}
 
int Solve(int x){
	
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}

const int M=2e6+5;
int er[100],s[100];
int Sum=0;
void Geter(int x,int y,int cntx,int cnty){
//	cout<<"now"<<x<<" "<<y<<' '<<cntx<<" "<<cnty<<"@ "<<Sum<<endl;
	if(x<=2&&y<=2) return;
	int xx,yy,cx=0,cy=0;
	if(x&1) Sum+=cntx;
	if(y&1) Sum+=cnty;
	if(x&1){
		xx=x/2;yy=x/2+1;
		cx++;cy++;
		if(x==y){
			cx++;cy++;
		}
		else{
			if(xx==y/2) cx+=2;
			else cy+=2;
		}
	}
	else{
		xx=x/2;cx+=2;
		if(x==y){
			cx+=2;
		}
		else{
			if(y/2==xx) yy=y/2+1;
			else yy=y/2;
			cx++;cy++;
		}
	}
	Geter(xx,yy,cx*cntx,cy*cnty);
	return;
}

int ksm(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;y>>=1;
	}
	return ans;
}

int Getcnt(int x,int y){
	/*if(y==1) return x;
	int ans=0;
	if(y&1){
		ans=2*(Getcnt(x/2,y/2)*Getcnt(x/2,y/2+1));
	}
	else{
		ans=Getcnt(x/2,y/2);
		ans=ans*ans;
	}
	return ans;*/
	
	int mi=0;Sum=0;
	while(er[mi]*y<=x) mi++;
	mi--;
	int cnt1=(x-y*er[mi])/er[mi];
	int cnt2=y-cnt1;
	int cnt3;
	if(y&1){
		if(y!=1) Sum++;
		Geter(y/2,y/2+1,1,1);
	}
	else Geter(y/2,y/2,1,1);
	cnt3=Sum;
	//cout<<cnt1<<" "<<cnt2<<" "<<cnt3<<endl;
	int ans=ksm(er[mi],cnt2)*ksm(er[mi+1],cnt1)*er[cnt3];
	return ans;
	
}

int Solve(int x){
	
	int mi=0;
	while(x>s[mi]){
		mi++;
	}
	int tot=er[mi];
	int now=x-s[mi-1];
	return Getcnt(tot,now);
	
}


signed main(){
	
	//freopen("1.in","r",stdin);
	
	er[0]=1;s[0]=1;
	for(int i=1;i<=100;i++) er[i]=er[i-1]*2;
	for(int i=1;i<=100;i++) s[i]=s[i-1]+er[i];
	
	int T;cin>>T;
	while(T--){
		
		int x=getint();
		if(x<=1){
			cout<<1<<"\n";continue;
		}
		cout<<Solve(x)<<"\n";
		
	}
	
	return 0;
}
	int mi=0;
	while(x>s[mi]){
		mi++;
	}
	int tot=er[mi];
	int now=x-s[mi-1];
	return Getcnt(tot,now);
	
}
 
 
signed main(){
	
	//freopen("1.in","r",stdin);
	
	er[0]=1;s[0]=1;
	for(int i=1;i<=100;i++) er[i]=er[i-1]*2;
	for(int i=1;i<=100;i++) s[i]=s[i-1]+er[i];
	
	int T;cin>>T;
	while(T--){
		
		int x=getint();
		if(x<=1){
			cout<<1<<"\n";continue;
		}
		cout<<Solve(x)<<"\n";
		
	}
	
	return 0;
}
