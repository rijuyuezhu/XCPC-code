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
const int P = 998244353, inv2 = 499122177;
const int MAXN = 2e5 + 5, MAXV = 1e6 + 5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, a[MAXN], mv, f[MAXV], g[MAXV], pr[MAXV], ip[MAXV], tot, mu[MAXV], inv[MAXV], ans;
void sieve(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = P-1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) mu[i * pr[j]] = mns(0, mu[i]);
			else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
	inv[1] = 1; for(int i = 2; i <= n; i++) inv[i] = mul(P - P/i, inv[P % i]);
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
		f[a[i]] = pls(f[a[i]], a[i]);
		mv = max(mv, a[i]);
	}
	sieve(mv);
	for(int i = 1; i <= mv; i++)
		for(int j = 1; j <= mv / i; j++) 
			g[i] = pls(g[i], f[i * j]);
	ans = 0;
	for(int i = 1; i <= mv; i++)
		for(int j = 1; j <= mv / i; j++)
			ans = pls(ans, 1ll * mu[j] * g[i * j] % P * g[i * j] % P * inv[i] % P);
	for(int i = 1; i <= n; i++) ans = mns(ans, a[i]);
	ans = mul(ans, inv2);
	printf("%d\n", ans);
	return 0;
}
