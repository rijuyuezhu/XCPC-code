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
const int MAXN = 1e6 + 5;
const int P = 998244353;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (const mint& a, const mint& b) { return MOD(a.v + b.v); }
mint operator - (const mint& a, const mint& b) { return MOD(a.v - b.v + P); }
mint operator - (const mint& a) { return 0-a; }
mint operator * (const mint& a, const mint& b) { return 1ll * a.v * b.v % P; }
mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
int n, k;
mint g[MAXN], f[MAXN], c[MAXN], invc[MAXN];
int pr[MAXN], ip[MAXN], tot;
void Sieve(int n) {
	ip[1] = 1; c[1] = 0;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i; c[i] = 1;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			c[k] = c[i] + 1;
			ip[k] = 1;
			if(i % pr[j] == 0) break;
		}
	}
	for(int i = 1; i <= n; i++) c[i] = -c[i], invc[i] = qpow(c[i]);
}
void Div(mint* f, mint* g, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = f[i];
	mint iv = qpow(g[1]);
	for(int i = 1; i <= n; i++) {
		ans[i] = ans[i] * iv;
		for(int j = 2; j <= n / i; j++) {
			ans[i * j] = ans[i * j] - ans[i] * g[j];
		}
	}
}
void Deriv(mint* f, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = f[i] * c[i];
}
void Integ(mint* f, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = f[i] * invc[i];
}
void Ln(mint* f, mint* ans, int n) {
	static mint tmp[MAXN];
	Deriv(f, tmp, n);
	Div(tmp, f, ans, n);
	Integ(ans, ans, n);
}
void Exp(mint* f, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = 0;
	ans[1] = 1;
	for(int i = 1; i <= n; i++) {
		if(i != 1) ans[i] = ans[i] * invc[i];
		for(int j = 2; j <= n / i; j++)
			ans[i * j] = ans[i * j] + ans[i] * f[j] * c[j];
	}
}
int main() {
	n = read(), k = read();
	Sieve(n);
	for(int i = 1; i <= n; i++) f[i] = read();
	mint invk = qpow(k);
	Ln(f, g, n);
	for(int i = 1; i <= n; i++) g[i] = g[i] * invk;
	Exp(g, f, n);
	for(int i = 1; i <= n; i++) printf("%d ", f[i].v);
	return 0;
}
