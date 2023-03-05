#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int MAXN = (1 << 14) + 5, BAS = 1 << 14, P = 998244353, MAXp = 55;
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint operator + (const mint& a, const mint& b) {return mint(MOD(a.v + b.v));}
mint operator - (const mint& a, const mint& b) {return mint(MOD(a.v - b.v + P));}
mint operator * (const mint& a, const mint& b) {return mint(1ll * a.v * b.v % P);}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
namespace Poly {
	typedef vector<mint> poly;
	mint _g[MAXN], inv[MAXN], fac[MAXN], ifac[MAXN];
	int tr[MAXN];
	void init() {
		_g[0] = 1; _g[1] = qpow(3, (P-1) / BAS);
		for(int i = 2; i < BAS; i++) 
			_g[i] = _g[i-1] * _g[1];
		inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = inv[P % i] * (P - P / i);
		fac[0] = ifac[0] = 1;
		for(int i = 1; i < MAXN; i++) {
			fac[i] = fac[i-1] * i;
			ifac[i] = ifac[i-1] * inv[i];
		}
	}
	int glim(int n) {
		int lim = 1; for(; lim < n; lim <<= 1);
		return lim;
	}
	void tpre(int lim) {
		for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
	}
	void DFT(poly& f, int lim) {
		if((int)f.size() < lim) f.resize(lim);
		tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) 
			for(int i = 0; i < lim; i += l)
				for(int j = i; j < i + k; j++) {
					mint tt = f[j+k] * _g[BAS / l * (j-i)];
					f[j+k] = f[j] - tt;
					f[j] = f[j] + tt;
				}
	}
	void IDFT(poly& f, int lim) {
		DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
		for(int i = 0; i < lim; i++) f[i] = f[i] * inv[lim];
	}
	poly Mul(poly f, poly g) {//limit the up_limit
		int n = f.size();
		int lim = glim(n+n);
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = f[i] * g[i];
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Pls(poly f, const poly& g) {
		if(f.size() < g.size()) f.resize(g.size());
		for(int i = 0; i < (int)g.size(); i++)
			f[i] = f[i] + g[i];
		return f;
	}
	void Clr(poly& f) {
		for(int i = 0; i < (int)f.size(); i++) f[i] = 0;
	}
}
using namespace Poly;
int n, p, m, p10;//p10 refer to 10 ^ (nown) mod p
poly f[MAXN], g[MAXN];
void solve(int n) {
	if(!n) {
		g[0][0] = 1, p10 = 1;
		return ;
	}
	solve(n >> 1);
	for(int i = 0; i < p; i++) f[i] = g[i], Clr(g[i]);
	for(int i = 0; i < p; i++)
		for(int j = 0; j < p; j++) {
			int nxt = (1ll * p10 * i + j) % p;
			g[nxt] = Pls(g[nxt], Mul(f[i], f[j]));
		}
	if(n & 1) {
		for(int i = 0; i < p; i++) f[i] = g[i], Clr(g[i]);
		for(int i = 0; i < p; i++)
			for(int j = 0; j <= m; j++)
				for(int k = 0; k <= 9 && j + k <= m; k++) {
					int nxt = (10 * i + k) % p;
					g[nxt][j + k] = g[nxt][j + k] + f[i][j];
				}
	}
	p10 = 1ll * p10 * p10 % p; if(n & 1)  p10 = 1ll * p10 * 10 % p;
}
int main() {
	init();
	n = read(); p = read(); m = read();
	for(int i = 0; i < p; i++) f[i].resize(m+1), g[i].resize(m+1);
	solve(n);
	mint ans = 0;
	for(int i = 0; i <= m; i++) {
		ans = ans + g[0][i];
		printf("%d ", ans.v);
	}
	return 0;
}
