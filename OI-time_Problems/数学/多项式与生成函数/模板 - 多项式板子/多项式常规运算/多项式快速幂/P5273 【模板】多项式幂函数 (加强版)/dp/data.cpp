#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
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
ll n, m;
int main() {
	srand(time(0));
	n = 20; m = 1ll * rand() * rand();
	printf("%lld %lld\n", n, m);
	for(int i = 0; i < n; i++) printf("%lld ", rand() % 100 <= 50 ? 0 : 1ll * rand() * rand() % 998244353);
	return 0;
}
