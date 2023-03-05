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
#define clr(f, s, e) memset(f+(s), 0x00, sizeof(int) * ((e) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 18) + 1, P = 998244353, G = 3, invG = 332748118;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int tf, tr[MAXN], _g[2][MAXN], inv[MAXN];
namespace Sqrt_P {
	int a, I2;
	struct F2 {int x, y;};
	F2 operator * (const F2& a, const F2& b) {return (F2){pls(mul(a.x, b.x), mul(mul(a.y, b.y), I2)), pls(mul(a.x, b.y), mul(a.y, b.x))};}
	F2 qpow2(F2 a, int n) {F2 ret = (F2){1, 0}; for(; n; n >>= 1, a = a * a) if(n & 1) ret = a * ret;  return ret;}
	int solve(int n) {
		n %= P;
		if(!n) return 0;
		if(qpow(n, (P-1) / 2) == P-1) return -1;
		while(1) {
			a = rand() % P;
			I2 = mns(mul(a, a), n);
			if(qpow(I2, (P-1) / 2) == P-1) break;
		}
		int ret = qpow2((F2){a, 1}, (P+1) / 2).x;
		return min(ret, P-ret);
	}
}
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
void Sqrt(int* f, int* g, int n) {
	static int a[MAXN], b[MAXN];
	if(n == 1) {g[0] = Sqrt_P::solve(f[0]); return ;}
	Sqrt(f, g, (n+1) >> 1); int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	Inv(g, b, n); clr(b, n, lim);
	Mul(a, b, a, n);
	for(int i = 0; i < n; i++) g[i] = mul(inv[2], pls(g[i], a[i]));
	clr(g, n, lim);
}
int n, f[MAXN], g[MAXN];
int main() {
	init();
	n = read();
	for(int i = 0; i < n; i++) f[i] = read();
	Sqrt(f, g, n);
	for(int i = 0; i < n; i++) printf("%d ", g[i]);
	return 0;
}
