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
#define clr(f, s, e) memset((f) + (s), 0x00, sizeof(int) * ((e) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 18) + 5, P = 998244353, bas = 1 << 18;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int tr[MAXN], tf, _g[MAXN], inv[MAXN];
void init() {
	inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P-P/i, inv[P % i]);
	_g[0] = 1; _g[1] = qpow(3, (P-1) / bas);
	for(int i = 2; i < bas; i++) _g[i] = mul(_g[i-1], _g[1]);
}
int getlim(int n) {
	int lim = 1; for(; lim < n+n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void DFT(int* f, int lim) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l)
			for(int j = i; j < i + k; j++) {
				int tt = mul(f[j+k], _g[bas / l * (j-i)]);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
}
void IDFT(int* f, int lim) {
	DFT(f, lim); reverse(f+1, f+lim);
	for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
}
void Mul(int* f, int* g, int* h, int n) {
	static int a[MAXN], b[MAXN];
	int lim = getlim(n);
	cpy(f, a, n); clr(a, n, lim);
	cpy(g, b, n); clr(b, n, lim);
	DFT(a, lim), DFT(b, lim);
	for(int i = 0; i < lim; i++) h[i] = mul(a[i], b[i]);
	IDFT(h, lim); clr(h, n, lim);
}
void Inv(int* f, int* g, int n) {
	static int a[MAXN];
	if(n == 1) {g[0] = qpow(f[0], P-2); return ;}
	Inv(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	DFT(g, lim); DFT(a, lim);
	for(int i = 0; i < lim; i++) g[i] = mul(g[i], mns(2, mul(a[i], g[i])));
	IDFT(g, lim); clr(g, n, lim);
}
void Deriv(int* f, int* g, int n) {
	for(int i = 1; i < n; i++) g[i-1] = mul(f[i], i);
	g[n-1] = 0;
}
void Integ(int* f, int* g, int n) {
	for(int i = 1; i < n; i++) g[i] = mul(f[i-1], inv[i]);
	g[0] = 0;
}
void Ln(int* f, int* g, int n) {
	static int a[MAXN], b[MAXN];
	int lim = getlim(n);
	Deriv(f, a, n); Inv(f, b, n);
	clr(a, n, lim); clr(b, n, lim);
	DFT(a, lim); DFT(b, lim);
	for(int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
	IDFT(a, lim); Integ(a, g, n);
}
void Exp(int* f, int* g, int n) {
	static int a[MAXN];
	if(n == 1) {g[0] = 1; return ;}
	Exp(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	Ln(g, a, n); clr(a, n, lim);
	for(int i = 0; i < n; i++) a[i] = mns(f[i], a[i]);
	a[0] = pls(a[0], 1);
	DFT(a, lim); DFT(g, lim);
	for(int i = 0; i < lim; i++) g[i] = mul(a[i], g[i]);
	IDFT(g, lim); clr(g, n, lim);
}
int n, m, f[MAXN], g[MAXN], cnt[MAXN];
int main() {
	init();
	n = read(), m = read();
	for(int i = 1; i <= n; i++) cnt[read()]++;
	for(int i = 1; i <= m; i++) if(cnt[i]) 
		for(int j = 1; 1ll * i * j <= m; j++)
			f[i * j] = pls(f[i * j], mul(cnt[i], inv[j]));
	Exp(f, g, m+1);
	for(int i = 1; i <= m; i++) printf("%d\n", g[i]);
	return 0;
}
