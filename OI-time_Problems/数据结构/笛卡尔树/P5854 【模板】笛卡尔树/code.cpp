#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '1' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e7 + 5;
int n, p[MAXN], ls[MAXN], rs[MAXN], stk[MAXN], _stk;
ll ans1, ans2;
int main() {
	n = read();
	for(int i = 1; i <= n; i++) p[i] = read();
	for(int i = 1; i <= n; i++) {
		int cur = _stk;
		while(cur && p[stk[cur]] > p[i]) cur--;
		if(cur) rs[stk[cur]] = i;
		if(cur < _stk) ls[i] = stk[cur+1];
		stk[_stk = ++cur] = i;
	}
	for(int i = 1; i <= n; i++) ans1 ^= 1ll * i * (ls[i] + 1), ans2 ^= 1ll * i * (rs[i] + 1);
	printf("%lld %lld\n", ans1, ans2);
	return 0;
}
