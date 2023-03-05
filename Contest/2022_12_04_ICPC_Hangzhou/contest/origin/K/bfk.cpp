#include<cstdio>
#include<cstring>
using namespace std;
char s[1000005];
long long f[26][26],sn[1000005][26],sz[1000005],t=1;
int main()
{
	int n,q;
	scanf("%d %d",&n,&q);
	while (n--)
	{
		scanf("%s",s);
		int l=strlen(s),curr=1;
		for (int i=0;i<l;i++)
		{
			for (int j=0;j<26;j++)
				if (sn[curr][j]) 
					f[s[i]-'a'][j]+=sz[sn[curr][j]];
			if (!sn[curr][s[i]-'a'])
				sn[curr][s[i]-'a']=++t;
			curr=sn[curr][s[i]-'a'];
			sz[curr]++;	
		}
	}
	while (q--)
	{
		scanf("%s",s);
		long long ans=0;
		for (int i=0;i<26;i++)
			for (int j=0;j<i;j++)
				ans+=f[s[j]-'a'][s[i]-'a'];
		printf("%lld\n",ans);
	}
	return 0;
}
