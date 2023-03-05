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
const int MAXN = (1 << 18)+5, Bas = 1 << 18, P = 998244353;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) :v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
namespace Poly {
	mint fac[MAXN], ifac[MAXN], inv[MAXN], _g[MAXN];
	int tr[MAXN];
	typedef vector<mint> poly;
	void init() {
		inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = (P-P/i) * inv[P % i];
		fac[0] = ifac[0] = 1;
		for(int i = 1; i < MAXN; i++) fac[i] = fac[i-1] * i, ifac[i] = ifac[i-1] * inv[i];
		_g[0] = 1; _g[1] = qpow(3, (P-1) / Bas);
		for(int i = 2; i < Bas; i++) _g[i] = _g[i-1] * _g[1];
	}
	int glim(int n) {
		int lim = 1;
		for(; lim < n; lim <<= 1);
		return lim;
	}
	void DFT(poly& f, int lim) {
		if((int)f.size() < lim) f.resize(lim);
		for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
		for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
			for(int i = 0; i < lim; i += l) 
				for(int j = i; j < i + k; j++) {
					mint tt = f[j+k] * _g[Bas / l * (j-i)];
					f[j+k] = f[j] - tt;
					f[j] = f[j] + tt;
				}
	}
	void IDFT(poly& f, int lim) {
		DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
		for(int i = 0; i < lim; i++) f[i] = f[i] * inv[lim];
	}
	poly Mul(poly f, poly g) {
		int n = f.size(), lim = glim(n+n);
		DFT(f, lim), DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = f[i] * g[i];
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Inv(poly f) {
		if((int)f.size() == 1) {poly g(1); g[0] = qpow(f[0]); return g;}
		int n = f.size(), lim = glim(n+n); poly g = f; g.resize((n+1)/2); g = Inv(g); 
		DFT(f, lim), DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = (2 - f[i] * g[i]) * g[i];
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Deriv(poly f) {
		int n = f.size();
		for(int i = 1; i < n; i++) f[i-1] = f[i] * i;
		f[n-1] = 0; return f;
	}
	poly Integ(poly f) {
		int n = f.size();
		for(int i = n-1; i >= 1; i--) f[i] = f[i-1] * inv[i];
		f[0] = 0; return f;
	}
	poly Ln(poly f) {
		return Integ(Mul(Deriv(f), Inv(f)));
	}
	poly Exp(poly f) {
		if((int)f.size() == 1) {poly g(1); g[0] = 1; return g;}
		int n = f.size(), lim = glim(n+n); poly g = f; g.resize((n+1)/2); g = Exp(g); g.resize(n);
		poly h = Ln(g);
		f[0] = f[0] + 1; for(int i = 0; i < n; i++) f[i] = f[i] - h[i];
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = f[i] * g[i];
		IDFT(f, lim); f.resize(n); return f;
	}
} using namespace Poly;
int n;
mint solve(int m) {
	poly f(n-1);
	for(int i = 0; i <= min(m, n-2); i++) f[i] = ifac[i];
	f = Ln(f);
	for(int i = 0; i < n-1; i++) f[i] = f[i] * n;
	f = Exp(f);
	return f[n-2] * fac[n-2];
}
int main() {
	init();
	n = read(); int m = read();
	printf("%d\n", (solve(m-1) - solve(m-2)).v);
	return 0;
}
