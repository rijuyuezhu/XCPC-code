#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
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
const int MAXN = (1 << 19) + 5, bas = 1 << 19;
const db PI = acos(-1.0);
int P;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
struct cp {db x, y;};
cp operator + (const cp& a, const cp& b) {return (cp){a.x + b.x, a.y + b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x - b.x, a.y - b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};}
cp operator * (const cp& a, const db& k) {return (cp){a.x * k, a.y * k};}
const cp I = (cp){0, 1};
cp _g[2][MAXN];
int tr[MAXN], tf;
void init() {
	for(int i = 0; i < bas; i++) {
		db a = cos(2 * PI * i / bas), b = sin(2 * PI * i / bas);
		_g[1][i] = (cp){a, b};
		_g[0][i] = (cp){a, -b};
	}
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(tf == lim) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
ll tran(db x) {return ((ll)(x > 0 ? x + .5 : x - .5) % P + P) % P;}
void FFT(cp* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l)
			for(int j = i; j < i+k; j++) {
				cp tt = f[j+k] * _g[fl][(j-i) * (bas / l)];
				f[j+k] = f[j] - tt;
				f[j] = f[j] + tt;
			}
	if(!fl) for(int i = 0; i < lim; i++) f[i].x /= lim, f[i].y /= lim;
}
void Mul(int* f, int* g, int* h, int n) {
	static cp f0[MAXN], f1[MAXN], g0[MAXN], g1[MAXN];
	int lim = getlim(n);
	for(int i = 0; i < n; i++) f0[i].x = f[i] >> 15, f0[i].y = f[i] & 32767;
	for(int i = 0; i < n; i++) g0[i].x = g[i] >> 15, g0[i].y = g[i] & 32767;
	for(int i = n; i < lim; i++) f0[i] = (cp){0, 0};
	for(int i = n; i < lim; i++) g0[i] = (cp){0, 0};
	FFT(f0, lim, 1); FFT(g0, lim, 1);
	for(int i = 0; i < lim; i++) {
		f1[i] = f0[i ? lim - i : 0], f1[i].y *= -1;
		g1[i] = g0[i ? lim - i : 0], g1[i].y *= -1;
	}
	for(int i = 0; i < lim; i++) {
		cp a = (f0[i] + f1[i]) * 0.5;		//f0
		cp b = (f1[i] - f0[i]) * 0.5 * I;	//f1
		cp c = (g0[i] + g1[i]) * 0.5;		//g0
		cp d = (g1[i] - g0[i]) * 0.5 * I;	//g1
		f0[i] = a * c + I * (a * d + b * c);
		g0[i] = b * d;
	}
	FFT(f0, lim, 0); FFT(g0, lim, 0);
	for(int i = 0; i < n; i++)
		h[i] = (1ll * tran(f0[i].x) * (1 << 30) + 1ll * tran(f0[i].y) * (1 << 15) % P + tran(g0[i].x)) % P;
	clr(h, n, lim);
}
int n, m, f[MAXN], g[MAXN], h[MAXN];
int main() {
	n = read(), m = read(); P = read();
	init();
	for(int i = 0; i <= n; i++) f[i] = read();
	for(int i = 0; i <= m; i++) g[i] = read();
	Mul(f, g, h, n+m+1);
	for(int i = 0; i <= n+m; i++) printf("%d ", h[i]);
	return 0;
}
