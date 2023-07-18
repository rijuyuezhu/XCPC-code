#include<cstdio>
using namespace std;
const long long MOD=1000000007;
int Odd[200005],Even[200005];
int Head[200005],Next[400005],To[400005],t,ANS;
void add(int a,int b)
{
	Next[++t]=Head[a];
	Head[a]=t;
	To[t]=b;
}
long long muti (long long w,int t)
{
	long long ans=1;
	while (t)
	{
		if (t&1) ans=(ans*w)%MOD;
		w=(w*w)%MOD;
		t>>=1;
	}
	return ans;
}
void Dfs1(int u,int f)
{
	Odd[u]=Even[u]=0;
	for (int i=Head[u];i;i=Next[i])
		if (To[i]!=f)
		{
			Dfs1(To[i],u);
			if ((Odd[To[i]]&1) || (Even[To[i]]&1)) Odd[u]++;
			else Even[u]++;
		}
}
void Dfs2 (int u,int f)
{
	if ((Odd[u]&1) || (Even[u]&1)) ANS++;
	for (int i=Head[u];i;i=Next[i])
		if (To[i]!=f)
		{
			if ((Odd[To[i]]&1) || (Even[To[i]]&1)) Odd[u]--;
			else Even[u]--;
			if ((Odd[u]&1) || (Even[u]&1)) Odd[To[i]]++;
			else Even[To[i]]++;			
			Dfs2(To[i],u);
			if ((Odd[u]&1) || (Even[u]&1)) Odd[To[i]]--;
			else Even[To[i]]--;	
			if ((Odd[To[i]]&1) || (Even[To[i]]&1)) Odd[u]++;
			else Even[u]++;				
		}	
}
void WORK()
{
	int n;
	scanf("%d",&n);
	t=0;
	for (int i=1;i<=n;i++) Head[i]=0;
	for (int i=1;i<n;i++)
	{
		int p,q;
		scanf("%d %d",&p,&q);
		add(p,q); add(q,p);
	}
//	printf("\n||\n");
	ANS=0;
	Dfs1(1,0);
//	printf("\n||\n");	
	Dfs2(1,0);
	printf("%lld\n",muti(n,MOD-2)*ANS%MOD);
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) WORK();
	return 0;
}
