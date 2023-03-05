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
#define clr(f, s, e) memset(f + (s), 0x00, sizeof(ll) * ((e) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(ll) * (n))
const int MAXN = (1 << 18)+5, P = 1004535809, G = 3, invG = 334845270;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll qpow(ll a, ll n) {ll ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
ll fac[MAXN], ifac[MAXN], inv[MAXN], _g[2][MAXN], tr[MAXN], pow2[MAXN], tf;
void init() {
	fac[0] = 1; for(int i = 1; i < MAXN; i++) fac[i] = mul(fac[i-1], i);
	ifac[MAXN-1] = qpow(fac[MAXN-1], P-2); for(int i = MAXN-2; i >= 0; i--) ifac[i] = mul(ifac[i+1], i+1);
	inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
	for(int l = 2; l < MAXN; l <<= 1) _g[1][l] = qpow(G, (P-1) / l), _g[0][l] = qpow(invG, (P-1) / l);
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(ll* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l) {
			ll gn = 1;
			for(int j = i; j < i+k; j++, gn = mul(gn, _g[fl][l])) {
				ll tt = mul(f[j+k], gn);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
		}
	if(!fl) {
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
	}
}
void Mul(ll* f, ll* g, ll* h, int n) {
	static ll a[MAXN], b[MAXN];
	int lim = getlim(n);
	cpy(f, a, n); clr(a, n, lim);
	cpy(g, b, n); clr(b, n, lim);
	NTT(a, lim, 1); NTT(b, lim, 1);
	for(int i = 0; i < lim; i++) h[i] = mul(a[i], b[i]);
	NTT(h, lim, 0); clr(h, n, lim);
}
void Inv(ll* f, ll* g, int n) {
	static ll a[MAXN];
	if(n == 1) {g[0] = qpow(f[0], P-2); return;}
	Inv(f, g, (n+1) >> 1);
	int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	NTT(g, lim, 1); NTT(a, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = (2 - a[i] * g[i] % P + P) * g[i] % P;
	NTT(g, lim, 0); clr(g, n, lim);
}
void Deriv(ll* f, ll* g, int n) {
	for(int i = 1; i < n; i++) g[i-1] = mul(f[i], i);
	g[n-1] = 0;
}
void Integ(ll* f, ll* g, int n) {
	for(int i = 1; i < n; i++) g[i] = mul(f[i-1], inv[i]);
	g[0] = 0;
}
void Ln(ll* f, ll* g, int n) {
	static ll a[MAXN], b[MAXN];
	Inv(f, a, n); Deriv(f, b, n);
	Mul(a, b, a, n); Integ(a, g, n);
}
int n;
ll f[MAXN], g[MAXN];
int main() {
	init();
	n = read();
	for(int i = 0; i <= n; i++) g[i] = mul(qpow(2, 1ll * i * (i-1) / 2), ifac[i]);
	Ln(g, f, n+1);
	printf("%lld\n", mul(f[n], fac[n]));
	return 0;
}
