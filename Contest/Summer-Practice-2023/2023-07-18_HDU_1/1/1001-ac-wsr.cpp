#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}

const int M=6005;

int etot,head[M],nex[M],go[M],f[M][16],dep[M];
int n,m,T;
struct Q{
	int id,l1,l2,s1,s2;
	Q(int Id,int L1,int S1,int L2,int S2){
		id=Id;l1=L1;l2=L2;s1=S1;s2=S2;
	}
};

inline void Addedge(int u,int v){
	nex[++etot]=head[u];head[u]=etot;go[etot]=v;
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;f[u][0]=fa;
	for(int i=1;i<=15;i++) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=nex[i]){
		int v=go[i];if(v==fa) continue;
		dfs(v,u); 
	}
}

inline int Getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=15;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	}
	
	if(x==y) return x;
	
	for(int i=15;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];y=f[y][i];
		}
	}
	return f[x][0];
}


int cor[M],len1[M],len2[M],ans[M],ansval[M];
vector<Q> vec[M];

void Build(int id,int s1,int t1,int s2,int t2){
	
	for(int i=1;i<=n;i++) cor[i]=len1[i]=len2[i]=0;
	
	int lca1=Getlca(s1,t1),lca2=Getlca(s2,t2);
	
	int now=s1;int S1=0,S2=0;
	while(now!=lca1){
		cor[now]+=1;
		len1[now]=S1;S1++;
		now=f[now][0];
	}cor[now]+=1;len1[now]=S1;
	now=t1;
	while(now!=lca1){
		cor[now]+=1;S1++;
		now=f[now][0];
	}
	now=s2;
	while(now!=lca2){
		cor[now]+=2;
		len2[now]=S2;S2++;
		now=f[now][0];
	}cor[now]+=2;len2[now]=S2;
	now=t2;
	while(now!=lca2){
		cor[now]+=2;S2++;
		now=f[now][0];
	}
	
	int P1=0,P2=0;
	now=s1;
	while(now!=lca1){
		if(cor[now]==3){
			if(0==P1) P1=now;
			else if(P1!=now) P2=now;
			break;
		}
		now=f[now][0];
	}
	if(cor[now]==3){
		if(0==P1) P1=now;
		else if(P1!=now) P2=now;
	}
	now=t1;
	while(now!=lca1){
		if(cor[now]==3){
			if(0==P1) P1=now;
			else if(P1!=now) P2=now;
			break;
		}
		now=f[now][0];
	}
	now=s2;
	while(now!=lca2){
		if(cor[now]==3){
			if(0==P1) P1=now;
			else if(P1!=now) P2=now;
			break;
		}
		now=f[now][0];
	}
	if(cor[now]==3){
		if(0==P1) P1=now;
		else if(P1!=now) P2=now;
	}
	now=t2;
	while(now!=lca2){
		if(cor[now]==3){
			if(0==P1) P1=now;
			else if(P1!=now) P2=now;
			break;
		}
		now=f[now][0];
	}
	
	
	now=t1;int cnt=0;
	while(now!=lca1){
		len1[now]=S1-cnt;cnt++;
		now=f[now][0];
	}
	now=t2;cnt=0;
	while(now!=lca2){
		len2[now]=S2-cnt;cnt++;
		now=f[now][0];
	}
	
	for(int i=1;i<=n;i++){
		if(cor[i]==3){
			vec[i].push_back(Q(id,len1[i],S1,len2[i],S2));
		}	
	}
	
}
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;return ;
	}
	int xx,yy;
	exgcd(b,a%b,xx,yy);
	x=yy;y=xx-a/b*yy;
}
int Gcd(int x,int y){
	return (!y)?x:Gcd(y,x%y);
}

void Update(int id,int aa,int bb,int cc,int dd,int pos){
	int a=bb,b=-dd,c=cc-aa;
	if(c%Gcd(a,b)!=0) return;
	int x,y,g=Gcd(a,b);
	exgcd(a/g,b/g,x,y);
	x=x*c/g,y=y*c/g;
	
	if(x*a+y*b==-1){
		x=-x,y=-y;
	}
	b=-b;
	if(x<0){
		int ha=abs(x)/b+1;
		x+=b*ha;y+=a*ha;
	}
	if(y<0){
		int ha=abs(y)/a+1;
		x+=b*ha;y+=a*ha;
	}
	while(x-b>=0&&y-a>=0){
		x-=b;y-=a;
	}
	if(ansval[id]>aa+bb*x){
		ansval[id]=aa+bb*x;
		ans[id]=pos;
	}
}

void Solve(){
	for(int i=1;i<=n;i++){
		for(auto it: vec[i]){
			int l1=it.l1,s1=it.s1,l2=it.l2,s2=it.s2;
			Update(it.id,l1,2*s1,l2,2*s2,i);
			Update(it.id,l1,2*s1,2*s2-l2,2*s2,i);
			Update(it.id,2*s1-l1,2*s1,l2,2*s2,i);
			Update(it.id,2*s1-l1,2*s1,2*s2-l2,2*s2,i);
		}
	}
}

void Clear(){
	etot=0;
	for(int i=1;i<=n;i++) head[i]=len1[i]=len2[i]=cor[i]=ans[i]=0;
	for(int i=1;i<=n;i++) vec[i].clear();
	
}

int main(){
	
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1,u,v;i<n;i++){
			u=getint();v=getint();
			Addedge(u,v);Addedge(v,u);
		}
		dfs(1,0);
		for(int i=1,t1,t2,s1,s2;i<=m;i++){
			
			s1=getint();t1=getint();s2=getint();t2=getint();
			Build(i,s1,t1,s2,t2);
			
		}
		
		for(int i=1;i<=m;i++) ansval[i]=1e9;
		Solve();
		for(int i=1;i<=m;i++){
			if(ansval[i]==1e9){
				cout<<-1<<"\n";
			}
			else cout<<ans[i]<<"\n";
		}
		
		Clear();
	}
	
	
	return 0;
}
