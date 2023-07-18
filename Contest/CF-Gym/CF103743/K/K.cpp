#include<cstdio>
using namespace std;
char ans[1000001];
int cnt[50];
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int n;
		scanf("%d",&n);
		printf("nunhehhe");
		for (int i = 0; i < 50; i++)
			cnt[i] = 0;
		int _cnt = 0;
		while (n) {
			if (n & 1)
				cnt[_cnt]++, cnt[1]++;
			_cnt++;
			n >>= 1;
		}
		for (int i = _cnt; i >= 1; i--) {
			for (int j = 1; j <= cnt[i]; j++)
				putchar('h');
			putchar('a');
		}
		putchar('\n');
		
	}
	return 0;
}
