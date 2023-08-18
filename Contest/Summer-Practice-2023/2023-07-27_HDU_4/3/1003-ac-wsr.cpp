#include<bits/stdc++.h>
using namespace std;
inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}

const int M=5e6+5;

int n,m,h=1,t=0,c,tot=0,Numcor[M],q[M],diff=0,Up;
struct node{
	int cor,num;
	node(int x=0,int y=0){
		cor=x;num=y;
	}
	inline bool operator < (const node &x) const{
		return num<x.num;
	}
}a[M];

inline void Add(int id){
	if(!Numcor[a[id].cor]){
		diff++;Numcor[a[id].cor]=1;
	}
	else Numcor[a[id].cor]++;
}

inline void Del(int id){
	if(Numcor[a[id].cor]==1){
		diff--;Numcor[a[id].cor]=0;
	}
	else Numcor[a[id].cor]--;
}

inline bool IsOK(){
	return diff==c;
}
inline void Check(){
	h=1,t=0;diff=0;
	for(int i=1;i<=c;i++) Numcor[i]=0;
	
	for(int i=1;i<=tot;i++){
		
		q[++t]=i;
		Add(q[t]);
		if(diff==c) Up=min(Up,a[q[t]].num-a[q[h]].num);
		while(h<=t){
			Del(q[h]);
			if(diff<c){
				Add(q[h]);
				break;
			}
			else{
				h++;
				Up=min(Up,a[q[t]].num-a[q[h]].num);
			}
		}
	}
	cout<<Up<<"\n";	
}

void Solve(){
	
	cin>>c;
	for(int i=1;i<=c;i++){
		
		n=getint();
		for(int j=1;j<=n;j++){
			int cor,num;
			cor=i;num=getint();
			a[++tot]=node(cor,num);
		}
		
	}
	sort(a+1,a+tot+1);
	//for(int i=1;i<=tot;i++) cout<<a[i].cor<<" "<<a[i].num<<endl;
	
	/*int Up=a[tot].num-a[1].num,Down=0;
	while(Down<=Up){
		//cout<<Down<<" "<<Up<<endl;
		if(Up-Down<=1){
			if(Check(Down)) cout<<Down<<"\n";
			else cout<<Up<<"\n";
			return;
		}
		int mid=Down+Up>>1;
		if(Check(mid)) Up=mid;
		else Down=mid+1;
	}*/
	Up=a[tot].num-a[1].num;
	Check();
	
}
void Clear(){
	tot=0;
}

int main(){
	
	int T;cin>>T;
	while(T--){
		Solve();
		Clear();
	}
	return 0;
}