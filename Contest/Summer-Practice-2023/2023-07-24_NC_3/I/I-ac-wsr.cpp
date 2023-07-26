#include<bits/stdc++.h>
using namespace std;

inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}

const int M=1e6+2,up=1e9;
int etot,head[M],nex[M],go[M],f[M/2][20],dep[M],n,m,rt,g[M/2][20],Up[M/2][60],Max[M/2],To[M/2][60],TT[M/2][60];
bool cor[M/2][60];
long long c[M];

inline void Addedge(int u,int v){
	nex[++etot]=head[u];head[u]=etot;go[etot]=v;
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;f[u][0]=fa;
	for(int i=0;i<60;i++){
		To[u][i]=u;
		if(cor[u][i]){
	    	
	    	if(cor[fa][i]){
	    		Up[u][i]=Up[fa][i]+1;
				To[u][i]=To[fa][i];
			}
			else Up[u][i]=0;
		}
		else Up[u][i]=0;
	}
	
//	cout<<"u= "<<u<<endl;
//	for(int i=0;i<=5;i++) cout<<To[u][i]<<" "<<Up[u][i]<<endl;
	   
	for(int i=0;i<60;i++){
		if(dep[u]-Up[u][i]<Max[u]){
			Max[u]=dep[u]-Up[u][i];
			TT[u][0]=To[u][i];
		}
	}
	
//	cout<<"Max= "<<Max[u]<<" "<<"TTO= "<<TT[u][0]<<endl;
	for(int i=1;i<=19;i++) TT[u][i]=TT[TT[u][i-1]][i-1];//;cout<<endl;
	
	g[u][0]=Max[u];
	for(int i=1;i<=19;i++) g[u][i]=g[TT[u][i-1]][i-1];
	for(int i=1;i<=19;i++) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=nex[i]){
		int v=go[i];if(v==fa) continue;
		dfs(v,u); 
	}
}

inline int Getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	}
	
	if(x==y) return x;
	
	for(int i=19;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];y=f[y][i];
		}
	}
	return f[x][0];
}

void Solve(int x,int y){
	
	int lca=Getlca(x,y);
	int ans=dep[x]-dep[lca]+dep[y]-dep[lca];
	
//	cout<<"lca= "<<lca<<' '<<"dis= "<<ans<<endl; 
	 
	int xx=x,ans1=0,ans2=0;
	//if(xx==lca) ans1--;
	for(int i=19;i>=0;i--){
		if(g[xx][i]>dep[lca]){
			//cout<<xx<<" "<<i<<" "<<" -> "<<g[xx][i]<<" "<<TT[x][i]<<endl;
			ans1+=(1<<i);
			xx=TT[xx][i];
		}
	}
	int yy=y;
	//if(yy==lca) ans2--;
	for(int i=19;i>=0;i--){
		if(g[yy][i]>dep[lca]){
		//	cout<<yy<<" "<<i<<" "<<" -> "<<g[yy][i]<<" "<<TT[yy][i]<<endl;
			ans2+=(1<<i);
			yy=TT[yy][i];
		}
	}
	
	long long X=0,Y=0;
	for(int i=0;i<60;i++) if(dep[To[xx][i]]<=dep[lca]&&cor[xx][i]) X|=(1ll<<i);
	for(int i=0;i<60;i++) if(dep[To[yy][i]]<=dep[lca]&&cor[yy][i]) Y|=(1ll<<i);
	int iff;
	if(X&Y) iff=0;else iff=1;
	
//	cout<<ans<<" + "<<ans1<<" "<<ans2<<" "<<iff<<endl; 

	
	cout<<(((ans+ans1+ans2+iff)>1000000)?-1:(ans+ans1+ans2+iff))<<"\n";
	
	
}

signed main(){
	
	cin>>n>>m;
	for(int i=0;i<=n;i++) Max[i]=up;
	//for(int i=0;i<60;i++) g[0][i]=up;
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	for(int i=1;i<=n;i++) for(int j=0;j<60;j++) if((1ll*c[i])&(1ll<<j)) cor[i][j]=1;
	for(int i=1,u,v;i<n;i++){
		u=getint();v=getint();
		Addedge(u,v);Addedge(v,u);
	}
	
	dfs(2,0);
	
	int x,y;
	while(m--){
		x=getint();y=getint();
		Solve(x,y);
	}
	
	
	return 0;
}

