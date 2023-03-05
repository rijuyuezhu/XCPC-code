#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = (1 << 18) + 5, Bas = (1 << 18), P = 998244353;
namespace MINT {
	struct mint {
		int v;
		mint(int v = 0) : v(v) {}
	};
	int MOD(int v) {return v >= P ? v - P : v;}
	mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
	mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
	mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
	mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
	mint operator += (mint& a, mint b) {return a = a + b;}
	mint operator -= (mint& a, mint b) {return a = a - b;}
	mint operator *= (mint& a, mint b) {return a = a * b;}
} using namespace MINT;
namespace Poly {
	typedef vector<mint> poly;
	mint inv[MAXN], fac[MAXN], ifac[MAXN], _g[MAXN];
	int tr[MAXN];
	void init() {
		inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = (P - P / i) * inv[P % i];
		fac[0] = ifac[0] = 1;
		for(int i = 1; i < MAXN; i++) fac[i] = fac[i-1] * i, ifac[i] = ifac[i-1] * inv[i];
		_g[0] = 1; _g[1] = qpow(3, (P-1) / Bas);
		for(int i = 2; i < Bas; i++) _g[i] = _g[i-1] * _g[1];
	}
	int glim(int n) {
		int lim = 1; for(; lim < n; lim <<= 1);
		return lim;
	}
	void DFT(poly& f, int lim) {
		if((int)f.size() < lim) f.resize(lim);
		for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
		for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) 
			for(int i = 0; i < lim; i += l)
				for(int j = i; j < i+k; j++) {
					mint tt = f[j+k] * _g[Bas / l * (j-i)];
					f[j+k] = f[j] - tt;
					f[j] = f[j] + tt;
				}
	}
	void IDFT(poly& f, int lim) {
		DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
		for(int i = 0; i < lim; i++) f[i] *= inv[lim];
	}
	namespace Expcalc {
		poly f, g;
		void cdq(int l, int r) {
			if(l + 1 == r) {
				if(l == 0) g[l] = 1;
				else g[l] *= inv[l];
				return ;
			}
			int m = (l + r) >> 1, n = r - l;
			cdq(l, m);
			poly p = poly(g.begin()+l, g.begin()+m), q = poly(f.begin(), f.begin()+n);
			DFT(p, n); DFT(q, n); //only need to n, for we need only (p*q)[n/2,n)
			for(int i = 0; i < n; i++) p[i] *= q[i];
			IDFT(p, n);
			for(int i = n / 2; i < n; i++) g[l + i] += p[i];
			cdq(m, r);
		}

	}
	poly Exp(poly _f) {
		using namespace Expcalc;
		int n = _f.size(), lim = glim(n);
		f.resize(lim), g.resize(lim);
		for(int i = 0; i < lim; i++) {
			f[i] = _f[i] * i;
			g[i] = 0;
		}
		cdq(0, lim); g.resize(n); return g;
	}
} using namespace Poly;
int main() {
	init();
	int n = read();
	poly f(n);
	for(int i = 0; i < n; i++) f[i] = read();
	f = Exp(f);
	for(int i = 0; i < n; i++) printf("%d ", f[i].v);
	printf("\n");
	return 0;
}
