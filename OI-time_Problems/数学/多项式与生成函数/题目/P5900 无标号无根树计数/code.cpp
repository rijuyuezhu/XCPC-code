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
const int MAXN = (1 << 19) + 5, Bas = 1 << 19, P = 998244353;
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
		inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = (P-P/i) * inv[P % i];
		fac[0] = ifac[0] = 1;
		for(int i = 1; i < MAXN; i++) {
			fac[i] = fac[i-1] * i;
			ifac[i] = ifac[i-1] * inv[i];
		}
		_g[0] = 1; _g[1] = qpow(3, (P-1)/Bas);
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
} using namespace Poly;
int n, lim;
poly f, g;
void cdq(int l, int r) {
	if(l + 1 == r) {
		if(l == 0 || l == 1) f[l] = l;
		else f[l] *= inv[l-1];
		if(l != 0) {
			for(int i = 1; i <= (lim-1) / l; i++)
				g[i * l] += f[l] * l;
		}
		return ;
	}
	int m = (l + r) >> 1, len = r - l;
	cdq(l, m);
	if(l != 0) {
		poly p = poly(f.begin() + l, f.begin() + m);
		poly q = poly(g.begin(), g.begin() + len);
		DFT(p, len); DFT(q, len);
		for(int i = 0; i < len; i++) p[i] *= q[i];
		IDFT(p, len);
		for(int i = len / 2; i < len; i++) f[l + i] += p[i];
		p = poly(g.begin() + l, g.begin() + m);
		q = poly(f.begin(), f.begin() + len);
		DFT(p, len); DFT(q, len);
		for(int i = 0; i < len; i++) p[i] *= q[i];
		IDFT(p, len);
		for(int i = len / 2; i < len; i++) f[l + i] += p[i];
	} else {
		poly p = poly(f.begin(), f.begin() + m);
		poly q = poly(g.begin(), g.begin() + m);
		DFT(p, len); DFT(q, len);
		for(int i = 0; i < len; i++) p[i] *= q[i];
		IDFT(p, len);
		for(int i = len / 2; i < len; i++) f[i] += p[i];
	}
	cdq(m, r);
}
int main() {
	init();
	n = read(), lim = glim(n+1);
	f.resize(lim), g.resize(lim);
	cdq(0, lim); f.resize(n+1);
	mint ans = f[n];
	for(int i = n / 2 + 1; i <= n-1; i++) ans -= f[i] * f[n-i];
	if(n % 2 == 0) ans -= f[n / 2] * (f[n / 2] - 1) * inv[2];
	printf("%d ", ans.v);
	return 0;
}
