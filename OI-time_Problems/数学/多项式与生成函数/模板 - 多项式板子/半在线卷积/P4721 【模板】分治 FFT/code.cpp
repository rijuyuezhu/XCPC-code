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
#define clr(f, s, t) memset((f) + (s), 0x00, sizeof(int) * ((t) - (s)))
#define cpy(f, g, n) memcpy((g), (f), sizeof(int) * (n))
const int MAXN = (1 << 18) + 5, bas = 1 << 18, P = 998244353, G = 3, invG = 332748118;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int _g[2][MAXN], tf, tr[MAXN];
void pre_gao() {
	_g[1][0] = _g[0][0] = 1;
	_g[1][1] = qpow(G, (P-1) / bas); _g[0][1] = qpow(invG, (P-1) / bas);
	for(int i = 2; i < bas; i++) {
		_g[1][i] = mul(_g[1][i-1], _g[1][1]);
		_g[0][i] = mul(_g[0][i-1], _g[0][1]);
	}
}
int getlim(int n) {
	int lim = 1; for(; lim < n+n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(tf == lim) return ;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(int* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) 
		for(int i = 0; i < lim; i += l)
			for(int j = i; j < i+k; j++) {
				int tt = mul(f[j+k], _g[fl][bas / l * (j-i)]);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
	if(!fl) {
		int in = qpow(lim, P-2);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], in);

	}
}
void solve(int* f, int* g, int l, int r) {//f = f_0 * g
	static int a[MAXN], b[MAXN];
	if(l >= r-1) return;
	int m = (l + r) >> 1;
	solve(f, g, l, m);
	int lim = getlim(r-l);
	cpy(f+l, a, m-l); clr(a, m-l, lim);
	cpy(g, b, r-l); clr(b, r-l, lim);
	NTT(a, lim, 1); NTT(b, lim, 1);
	for(int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
	NTT(a, lim, 0);
	for(int i = m; i < r; i++) f[i] = pls(f[i], a[i-l]);
	solve(f, g, m, r);
}
int n, f[MAXN], g[MAXN];
int main() {
	pre_gao();
	n = read();
	for(int i = 1; i < n; i++) g[i] = read();
	f[0] = 1; solve(f, g, 0, n);
	for(int i = 0; i < n; i++) printf("%d ", f[i]);
	return 0;
}
