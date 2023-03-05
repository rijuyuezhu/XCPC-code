#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
int n, m, k;
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
int main() {
	n = read(), m = read(), k = read();
	ll ret = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(gcd(i, j) == 1 && gcd(j, k) == 1)
				ret++;
	printf("%lld\n", ret);
	return 0;
}
