#include<bits/stdc++.h>
using namespace std;
#define int long long 
inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}


long long dist[1005][1005],p[1005][1005],ee[1005][1005];
long long e[1005][1005];
const long long INF=10000000000009,mod=998244353; 
int n,m;
struct node{
	int u;
	long long w;
	bool operator < (const node &a) const{
		return w>a.w;
	}	
}curr;
priority_queue <node> q;
void dij (int v)
{
	p[v][v]=1;
	curr.u=v; curr.w=0;
	q.push(curr);
	while (!q.empty())
	{
		curr=q.top();
		q.pop();
		int u=curr.u,w=curr.w;
		if (w!=dist[v][u]) continue;
		for (int i=1;i<=n*2;i++)
		{
            if (i==u) continue;
           // cout<<v<<' '<<u<<' '<<i<<"!\n";
			if (w+e[u][i]<dist[v][i])
			{
				dist[v][i]=curr.w=w+e[u][i];
				curr.u=i;
				p[v][i]=p[v][u];
				q.push(curr);
			}
			else if (w+e[u][i]==dist[v][i]){
				p[v][i]+=p[v][u];p[v][i]%=mod;
			}
		}
	}
}
void WORK()
{
	cin>>n>>m;

	for (int i=1;i<=n*2;i++)
		for (int j=1;j<=n*2;j++)
			ee[i][j]=0,e[i][j]=dist[i][j]=INF,p[i][j]=0;
	for (int i=1;i<=n;i++) e[i][i]=dist[i][i]=e[i][i+n]=dist[i][i+n]=0;
	for(int i=n+1;i<=2*n;i++) e[i][i]=dist[i][i]=0;

    while (m--)
    {
        int u,v;
        long long w;
        u=getint();v=getint();w=getint();
        ee[u][v]=w;//cout<<u<<" "<<v<<" --> "<<ee[u][v]<<endl;
    }
    map<int,int> mp;
    int ans=INF;
	for (int i=1;i<=n;i++) {
	//	cout<<i<<"@\n";
		for(int j=1;j<=i;j++){
			
		//	if(ee[i][j]) cout<<i<<" "<<j<<" "<<ee[i][j]<<endl;
			if(ee[i][j]) e[i+n][j]=ee[i][j];
			if(ee[j][i]) e[j+n][i]=ee[j][i];
			
		}
		
		
		
		dij(i+n);
		
		/*for(int ii=1;ii<=n*2;ii++){
			for(int jj=1;jj<=n*2;jj++){
				if(e[ii][jj]!=INF) cout<<ii<<" "<<jj<<"== "<<e[ii][jj]<<"\n";
			}
		}*/
		
		(mp[dist[i+n][i]]+=p[i+n][i])%=mod;
		ans=min(ans,dist[i+n][i]);
	}
	if(ans==INF){
		cout<<-1<<" "<<-1<<"\n";
	}
	else cout<<ans<<" "<<mp[ans]<<"\n";
	
   
}
signed main()
{
	int T;
    scanf("%lld",&T);
	while (T--) WORK();
    return 0;
}

