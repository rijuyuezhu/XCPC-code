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
#define clr(f, s, t) memset(f + (s), 0x00, sizeof(int) * ((t) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 18) + 5, G = 3, invG = 332748118, P = 998244353, inv2 = 499122177;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int tf, tr[MAXN], _g[2][MAXN];
void init() {
	for(int l = 2; l < MAXN; l <<= 1)
		_g[1][l] = qpow(G, (P-1) / l), _g[0][l] = qpow(invG, (P-1) / l);
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(tf == lim) return ;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(int* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) 
		for(int i = 0; i < lim; i += l) {
			int gn = 1;
			for(int j = i; j < i+k; j++, gn = mul(gn, _g[fl][l])) {
				int tt = mul(f[j+k], gn);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
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
	if(n == 1) {g[0] = qpow(f[0], P-2); return ;}
	Inv(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	NTT(a, lim, 1); NTT(g, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = mul(g[i], mns(2, mul(g[i], a[i])));
	NTT(g, lim, 0); clr(g, n, lim);
}
void Sqrt(int* f, int* g, int n) {
	static int a[MAXN], b[MAXN];
	if(n == 1) {g[0] = 1; return ;}//it is sure that f[0] = 1
	Sqrt(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	Inv(g, b, n); clr(b, n, lim);
	Mul(a, b, a, n); 
	for(int i = 0; i < n; i++) g[i] = mul(inv2, pls(g[i], a[i]));
	clr(g, n, lim);
}
int n, m, f[MAXN], g[MAXN];
int main() {
	init();
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		int k = read();
		if(k <= m) f[k] = 1;
	}
	for(int i = 0; i <= m; i++) g[i] = mns((i == 0), mul(4, f[i]));//g(x)=1-4f(x)
	Sqrt(g, f, m+1); //f(x)=sqrt(g(x))
	f[0] = pls(f[0], 1); //f(x)++
	Inv(f, g, m+1); //g(x)=1/f(x)
	for(int i = 0; i <= m; i++) g[i] = pls(g[i], g[i]); //g(i) *= 2
	for(int i = 1; i <= m; i++) printf("%d\n", g[i]);
	return 0;
}
