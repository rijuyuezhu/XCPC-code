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
const int MAXN = 15;
int n;
ll a[MAXN], b[MAXN];
ll qmul(ll a, ll b, ll mod) {
	if(a < b) swap(a, b);
	ll ret = 0;
	for(; b; b >>= 1, (a += a) %= mod)
		if(b & 1) (ret += a) %= mod;
	return ret;
}
void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a, ll p) {
	ll x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}
ll CRT() {
	ll M = 1, ans = 0;
	for(int i = 1; i <= n; i++) M *= a[i];
	for(int i = 1; i <= n; i++) {
		ll Mi = M / a[i];
		(ans += qmul(inv(Mi, a[i]) * b[i] % M, Mi, M)) %= M;
	}
	return ans;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), b[i] = read();
	printf("%lld\n", CRT());
	return 0;
}
