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
#define clr(f, s, t) memset(f+(s), 0x00, sizeof(int) * ((t) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 18) + 5, P = 998244353, G = 3, invG = 332748118;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a);  return ret;}
int _g[2][MAXN], tf, tr[MAXN];
void init() {
	for(int l = 2; l < MAXN; l <<= 1)
		_g[1][l] = qpow(G, (P-1) / l),
		_g[0][l] = qpow(invG, (P-1) / l);
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(int* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l)
			for(int j = i, gn = 1; j < i+k; j++, gn = mul(gn, _g[fl][l])) {
				int tt = mul(gn, f[j+k]);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
	if(!fl) {
		int in = qpow(lim, P-2);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], in);
	}
}
void Mul(int* f, int* g, int* h, int n) {
	static int a[MAXN], b[MAXN];
	int lim = getlim(n);
	cpy(f, a, n); clr(a, n, lim);
	cpy(g, b, n); clr(b, n, lim);
	NTT(a, lim, 1); NTT(b, lim, 1);
	for(int i = 0; i < lim; i++) h[i] = mul(a[i], b[i]);
	NTT(h, lim, 0); clr(h, n, lim);
}
void Inv(int* f, int* g, int n) {
	static int a[MAXN];
	if(n == 1) {g[0] = qpow(f[0], P-2); return;}
	Inv(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	NTT(a, lim, 1); NTT(g, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = mul(g[i], mns(2, mul(a[i], g[i])));
	NTT(g, lim, 0); clr(g, n, lim);
}
void Div(int* f, int* g, int* q, int* r, int n, int m) {
	static int a[MAXN], b[MAXN];
	int lim = getlim(n+1);
	cpy(g, a, m+1); reverse(a, a+m+1); clr(a, m+1, lim);
	Inv(a, b, n-m+1);
	cpy(f, a, n+1); reverse(a, a+n+1); clr(a, n+1, lim);
	Mul(a, b, q, n-m+1); reverse(q, q+n-m+1); clr(q, n-m+1, lim);
	Mul(g, q, a, m);
	for(int i = 0; i < m; i++) r[i] = mns(f[i], a[i]);
	clr(r, m, lim);
}
int n, m, f[MAXN], g[MAXN], q[MAXN], r[MAXN];
int main() {
	init();
	n = read(); m = read();
	for(int i = 0; i <= n; i++) f[i] = read();
	for(int i = 0; i <= m; i++) g[i] = read();
	Div(f, g, q, r, n, m);
	for(int i = 0; i <= n-m; i++) printf("%d ", q[i]);
	printf("\n");
	for(int i = 0; i <= m-1; i++) printf("%d ", r[i]);
	printf("\n");
	return 0;
}
