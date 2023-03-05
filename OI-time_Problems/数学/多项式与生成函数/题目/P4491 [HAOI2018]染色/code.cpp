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
const int MAXN = (1 << 18) + 5, bas = 1 << 18,  P = 1004535809, G = 3, MAXV = 1e7+5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int _g[MAXN], inv[MAXV], tr[MAXN], fac[MAXV], ifac[MAXV], tf;
void init() {
	_g[0] = 1; _g[1] = qpow(G, (P-1) / bas);
	for(int i = 2; i < bas; i++) _g[i] = mul(_g[i-1], _g[1]);
	inv[1] = 1; for(int i = 2; i < MAXV; i++) inv[i] = mul(P-P/i, inv[P % i]);
	fac[0] = 1; for(int i = 1; i < MAXV; i++) fac[i] = mul(fac[i-1], i);
	ifac[MAXV-1] = qpow(fac[MAXV-1], P-2); for(int i = MAXV-2; i >= 0; i--) ifac[i] = mul(ifac[i+1], i+1);
}
int getlim(int n) {
	int lim = 1; for(; lim < n+n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(tf == lim) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void DFT(int* f, int lim) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l)
			for(int j = i; j < i+k; j++) {
				int tt = mul(f[j+k], _g[bas / l * (j-i)]);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
}
void IDFT(int* f, int lim) {
	DFT(f, lim); reverse(f+1, f+lim);
	for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
}
int C(int n, int m) {return mul(fac[n], mul(ifac[m], ifac[n-m]));}
int n, m, s, w[MAXN], A[MAXN], B[MAXN];
int calcf(int k) {
	return n-k*s >= 0 ? mul(C(m, k), mul(fac[n], mul(qpow(ifac[s], k), mul(ifac[n - k*s], qpow(m-k, n - k*s))))) : 0;
}
int main() {
	init();
	n = read(), m = read(), s = read();
	for(int i = 0; i <= m; i++) w[i] = read();
	for(int i = 0; i <= m; i++) A[i] = mul(fac[i], calcf(i));
	for(int i = 0; i <= m; i++) B[m-i] = mul(i & 1 ? P-1 : 1, ifac[i]);
	int lim = getlim(m+1);
	DFT(A, lim); DFT(B, lim);
	for(int i = 0; i < lim; i++) A[i] = mul(A[i], B[i]);
	IDFT(A, lim);
	int ans = 0;
	for(int i = 0; i <= m; i++) ans = pls(ans, mul(w[i], mul(A[i+m], ifac[i])));
	printf("%d\n", ans);
	return 0;
}
