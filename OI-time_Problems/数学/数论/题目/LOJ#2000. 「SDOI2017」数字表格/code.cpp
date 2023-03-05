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
const int P = 1e9 + 7;
const int MAXN = 1e6 + 5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int inv(int a) {return qpow(a, P-2);}
int ip[MAXN], pr[MAXN], tot, mu[MAXN], f[MAXN], invf[MAXN], g[MAXN], invg[MAXN], n, m, ans;
void init(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i; mu[i] = -1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				mu[i * pr[j]] = -mu[i];
			} else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
	f[0] = 0; f[1] = 1; invf[1] = 1;
	for(int i = 2; i <= n; i++) {
		f[i] = pls(f[i-1], f[i-2]);
		invf[i] = inv(f[i]);
	}
	for(int i = 0; i <= n; i++) g[i] = 1;
	for(int i = 1; i <= n; i++)
		if(mu[i] == 1) {
			for(int j = 1; 1ll * i * j <= n; j++)
				g[i * j] = mul(g[i * j], f[j]);
		} else if(mu[i] == -1) {
			for(int j = 1; 1ll * i * j <= n; j++)
				g[i * j] = mul(g[i * j], invf[j]);
		}
	for(int i = 1; i <= n; i++) g[i] = mul(g[i], g[i-1]);
	for(int i = 0; i <= n; i++) invg[i] = inv(g[i]);
}
int main() {
	init(1e6);
	for(int t = read(); t; t--) {
		n = read(); m = read();
		ans = 1;
		for(int i = 1, j; i <= n && i <= m; i = j + 1) {
			int vn = n / i, vm = m / i; j = min(n / vn, m / vm);
			ans = mul(ans, qpow(mul(g[j], invg[i-1]), 1ll * vn * vm % (P-1)));
		}
		printf("%d\n", ans);
	}
	return 0;
}
