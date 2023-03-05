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
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}

int n, c[MAXN], m, ip[MAXN], pr[MAXN], tot, mu[MAXN];
mint f[MAXN], invf[MAXN], g[MAXN];
void sieve(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j]) {
				mu[k] = -mu[i];
			} else {
				mu[k] = 0;
				break;
			}
		}
	}
}
int main() {
	m = read();
	for(int i = 1; i <= m; i++) {
		int k = read();
		n = max(k, n);
		c[k]++;
	}
	f[0] = 0; f[1] = 1; invf[1] = 1;
	for(int i = 2; i <= n; i++) f[i] = f[i-1] + f[i-2], invf[i] = qpow(f[i]);
	sieve(n);
	for(int i = 1; i <= n; i++) g[i] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n / i; j++)
			if(mu[j] == 1) g[i * j] = g[i * j] * f[i];
			else if(mu[j] == -1) g[i * j] = g[i * j] * invf[i];
	mint ans = 1;
	for(int i = 1; i <= n; i++) {
		int cnt = 0;
		for(int j = 1; j <= n / i; j++)
			cnt += c[i * j];
		if(cnt) ans = ans * g[i];
	}
	printf("%d\n", ans.v);
	return 0;
}
