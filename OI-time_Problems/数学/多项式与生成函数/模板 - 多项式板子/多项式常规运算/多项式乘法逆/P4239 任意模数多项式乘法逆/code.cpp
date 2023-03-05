#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef long double db;
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
const int P = 1e9 + 7, MAXN = (1 << 20) + 5, bas = 1 << 20;
const db PI = acos((db)-1.0);
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
struct cp{db x, y;};
cp operator + (const cp& a, const cp& b) {return (cp){a.x + b.x, a.y + b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x - b.x, a.y - b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};}
cp operator * (const cp& a, const db& b) {return (cp){a.x * b, a.y * b};}
const cp I = (cp){0, 1};
cp _g[2][MAXN];
int tr[MAXN], tf;
void init() {
	for(int i = 0; i < bas; i++) {
		db a = cos(2 * PI / bas * i), b = sin(2 * PI / bas * i);
		_g[1][i] = (cp){a, b}; _g[0][i] = (cp){a, -b};
	}
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return;
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
	static cp a[MAXN], b[MAXN], c[MAXN], d[MAXN];
	int lim = getlim(n);
	for(int i = 0; i < n; i++) {
		a[i].x = f[i] >> 15; a[i].y = f[i] & 32767;
		c[i].x = g[i] >> 15; c[i].y = g[i] & 32767;
	}
	for(int i = n; i < lim; i++) a[i] = c[i] = (cp){0, 0};
	FFT(a, lim, 1); FFT(c, lim, 1);
	for(int i = 0; i < lim; i++) {
		b[i] = a[i ? lim - i : 0]; b[i].y *= -1;
		d[i] = c[i ? lim - i : 0]; d[i].y *= -1;
	}
	for(int i = 0; i < lim; i++) {
		cp aa = (a[i] + b[i]) * 0.5;		//f0
		cp bb = (b[i] - a[i]) * 0.5 * I;	//f1
		cp cc = (c[i] + d[i]) * 0.5;		//g0
		cp dd = (d[i] - c[i]) * 0.5 * I;	//g1
		a[i] = (aa * cc) + I * (aa * dd + bb * cc);
		b[i] = bb * dd;
	}
	FFT(a, lim, 0); FFT(b, lim, 0);
	for(int i = 0; i < n; i++)
		h[i] = ((1ll << 30) * tran(a[i].x) + (1ll << 15) * tran(a[i].y) + tran(b[i].x)) % P;
	clr(h, n, lim);
}
void Inv(int* f, int* g, int n) {
	static int a[MAXN];
	if(n == 1) {g[0] = qpow(f[0], P-2); return;}
	Inv(f, g, (n+1) >> 1);
	clr(g, (n+1) >> 1, n);
	Mul(g, g, a, n);
	Mul(f, a, a, n);
	for(int i = 0; i < n; i++) g[i] = mns(pls(g[i], g[i]), a[i]);
}
int n, f[MAXN], g[MAXN];
int main() {
	//freopen("code.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	init();
	n = read();
	for(int i = 0; i < n; i++) f[i] = read();
	Inv(f, g, n);
	for(int i = 0; i < n; i++) printf("%d ", g[i]);
	return 0;
}
