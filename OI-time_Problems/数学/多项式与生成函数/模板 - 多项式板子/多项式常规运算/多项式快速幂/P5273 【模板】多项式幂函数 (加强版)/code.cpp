#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
#define clr(f, s, t) memset(f + (s), 0x00, sizeof(int) * ((t) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXL = 1e5 + 5, MAXN = (1 << 18) + 5, P = 998244353, G = 3, invG = 332748118;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int tf, tr[MAXN], _g[2][MAXN], inv[MAXN];
void init() {
	inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
	for(int l = 2; l < MAXN; l <<= 1) _g[1][l] = qpow(G, (P-1) / l), _g[0][l] = qpow(invG, (P-1) / l);
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return ;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(int* f, int lim, int fl) {
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
	if(!fl)
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
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
	Inv(f, a, n); Deriv(f, b, n);
	Mul(a, b, a, n); Integ(a, g, n);
}
void Exp(int* f, int * g, int n) {
	static int a[MAXN], b[MAXN];
	if(n == 1) {g[0] = 1; return;}
	Exp(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	Ln(g, b, n); clr(b, n, lim);
	NTT(a, lim, 1); NTT(b, lim, 1); NTT(g, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = mul(g[i], pls(a[i], mns(1, b[i])));
	NTT(g, lim, 0); clr(g, n, lim);
}

void Qpow(int* f, int* g, int n, int k1, int k2, bool out) {
	static int a[MAXN];
	int shift = 0;
	if(k1 == 0) {
		clr(g, 0, n); g[0] = qpow(f[0], k2);
		return;
	}
	while(shift < n && !f[shift]) shift++;
	if((shift && out) || 1ll * shift * k1 >= n) {
		clr(g, 0, n);
		return;
	}
	int in = qpow(f[shift], P-2), t = qpow(f[shift], k2);
	for(int i = 0; i < n; i++) f[i] = i + shift < n ? mul(f[i + shift], in) : 0;
	Ln(f, a, n);
	for(int i = 0; i < n; i++) a[i] = mul(a[i], k1);
	Exp(a, f, n);
	shift *= k1;
	for(int i = 0; i < n; i++) g[i] = i - shift >= 0 ? mul(f[i - shift], t) : 0;
}
	
	

char sk[MAXL];
int n, f[MAXN], g[MAXN], len, out;
ll k1, k2;
int main() {
	init();
	n = read(); scanf("%s", sk+1); len = strlen(sk+1);
	for(int i = 0; i < n; i++) f[i] = read();
	for(int i = 1; i <= len; i++) {
		k1 = k1 * 10 + int(sk[i] - '0');
		if(k1 >= P) k1 %= P, out = 1;
	}
	for(int i = 1; i <= len; i++) {
		k2 = k2 * 10 + int(sk[i] - '0');
		if(k2 >= P-1) k2 %= P-1, out = 1;
	}
	Qpow(f, g, n, k1, k2, out);
	for(int i = 0; i < n; i++) printf("%d ", g[i]);
	return 0;
}
