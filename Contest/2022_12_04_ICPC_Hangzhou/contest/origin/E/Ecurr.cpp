#include<cstdio>
#include<queue>
using namespace std;
int step[6][6],movbx[6][6],movby[6][6];
queue < pair<int,int> > q;
int main()
{
	for (int i=1;i<5;i++)
	{
		step[i][i+1]=1;
		q.push(make_pair(i,i+1));		
	}
	int curr[6],nxt[6],s1,s2;
	while (!q.empty())
	{
		for (int i=1;i<6;i++)
			curr[i]=0;
		s1=q.front().first;
		s2=q.front().second;
		q.pop();
		curr[s1]=1;
		curr[s2]=2;	
		for (int x=1;x<4;x++)
			for (int y=1;x+y<5;y++)
			{
				for (int m=1;m<=x;m++)
					nxt[5-x+m]=curr[m];
				for (int n=1;n<=y;n++)
					nxt[n]=curr[5-y+n];
				for (int p=1;p<=5-x-y;p++)
					nxt[y+p]=curr[x+p];	 
				int s11,s22;	
				for (int w=1;w<=5;w++)
				{
					if (nxt[w]==1) s11=w;
					if (nxt[w]==2) s22=w;
				}
				if (!step[s11][s22])
				{
					step[s11][s22]=step[s1][s2]+1;
					movbx[s11][s22]=y;
					movby[s11][s22]=x;
					q.push(make_pair(s11,s22));
				}
			}
	}
	for (int i=1;i<=5;i++)
	{
		for (int j=1;j<=5;j++)
		{
			printf("%d ",step[i][j]);
						
		}
		printf("\n");
	}

	return 0;
}
