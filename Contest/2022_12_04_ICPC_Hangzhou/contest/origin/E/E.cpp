#include<cstdio>
using namespace std;
char str[6];
int l=5;
void swap(int x,int y)
{
	printf("( ");
	for (int i=y;i<=l;i++)
		printf("%c ",str[i]);
	for (int i=x+1;i<y;i++)
		printf("%c ",str[i]);
	for (int i=1;i<=x;i++)
		printf("%c ",str[i]);
	printf(") ");			
}
int main()
{
	for (int i=1;i<=5;i++)
		for (int j=1;j<=5;j++)
		{
			if (i==j) continue;
			for (int k=1;k<=l;k++) str[k]='*';
			str[i]='1';
			str[j]='2';
			printf("( ");
			for (int k=1;k<=l;k++) printf("%c ",str[k]);
			printf("):");
			printf("\n");
			for (int x=1;x<=l;x++)
				for (int y=x+2;y<=l;y++)
					swap(x,y);
			printf("\n");		
			
		}
	return 0;
}
