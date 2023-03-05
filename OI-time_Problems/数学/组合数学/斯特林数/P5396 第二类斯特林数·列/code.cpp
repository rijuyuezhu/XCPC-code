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
const int MAXN = (1 << 18) + 5, BAS = 1 << 18, P = 167772161; // g = 3
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n=P-2) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
namespace Poly {
	typedef vector<int> poly;
	int _g[MAXN], tr[MAXN], inv[MAXN], fac[MAXN], ifac[MAXN];
	void init() {
		_g[0] = 1; _g[1] = qpow(3, (P-1) / BAS);
		for(int i = 2; i < BAS; i++) _g[i] = mul(_g[i-1], _g[1]);
		inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P-P/i, inv[P % i]);
		fac[0] = ifac[0] = 1;
		for(int i = 1; i < MAXN; i++) {
			fac[i] = mul(fac[i-1], i); ifac[i] = mul(ifac[i-1], inv[i]);
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
		tpre(lim); if((int)f.size() < lim) f.resize(lim);
		for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
			for(int i = 0; i < lim; i += l) 
				for(int j = i; j < i+k; j++) {
					int tt = mul(f[j+k], _g[BAS / l * (j-i)]);
					f[j+k] = mns(f[j], tt);
					f[j] = pls(f[j], tt);
				}
	}
	void IDFT(poly& f, int lim) {
		DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
	}
	poly Rev(poly f) {
		reverse(f.begin(), f.end()); return f;
	}
	poly Pls(poly f, const poly& g) {
		f.resize(max(f.size(), g.size()));
		for(int i = 0; i < (int)g.size(); i++) f[i] = pls(f[i], g[i]);
		return f;
	}
	poly Mns(poly f, const poly& g) {
		f.resize(max(f.size(), g.size()));
		for(int i = 0; i < (int)g.size(); i++) f[i] = mns(f[i], g[i]);
		return f;
	}
	poly Mul(poly f, int k) {
		for(int i = 0; i < (int)f.size(); i++) f[i] = mul(f[i], k);
		return f;
	}
	poly Mul(poly f, poly g) {
		int n = f.size() + g.size() - 1, lim = glim(n);
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Mul(poly f, poly g, int n) {
		int lim = glim(f.size() + g.size() - 1);
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Inv(poly f) {
		if(f.size() == 1) {poly g(1); g[0] = qpow(f[0]); return g;}
		int n = f.size(), lim = glim(n+n);
		poly g = f; g.resize((n+1)/2); g = Inv(g);
		DFT(g, lim); DFT(f, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(g[i], mns(2, mul(f[i], g[i])));
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Deriv(poly f) {
		for(int i = 1; i < (int)f.size(); i++) f[i-1] = mul(f[i], i);
		f.pop_back(); return f;
	}
	poly Integ(poly f) {
		f.push_back(0);
		for(int i = f.size()-1; i > 0; i--) f[i] = mul(f[i-1], inv[i]);
		f[0] = 0; return f;
	}
	poly Ln(poly f) {
		return Integ(Mul(Deriv(f), Inv(f), f.size()-1));
	}
	poly Exp(poly f) {
		if(f.size() == 1) {poly g(1); g[0] = 1; return g;}
		int n = f.size(), lim = glim(n+n);
		poly g = f; g.resize((n+1)/2); g = Exp(g); g.resize(n);
		f = Mns(f, Ln(g)); f[0] = pls(f[0], 1);
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Qpow(poly f, int k) {
		int n = f.size(), shift = 0;
		if(k == 0) return poly(n);
		while(shift < n && !f[shift]) shift++;
		if(shift * k >= n) return poly(n);
		int in = qpow(f[shift]), t = qpow(f[shift], k);
		f = Ln(Mul(poly(f.begin()+shift, f.end()), in));
		for(int i = 0; i < (int)f.size(); i++) f[i] = mul(f[i], k);
		f = Mul(Exp(f), t);
		f.insert(f.begin(), shift * k, 0); f.resize(n);
		return f;
	}
}
using namespace Poly;
int n, k;
int main() {
	init();
	n = read(), k = read();
	poly f(n+1);
	for(int i = 1; i <= n; i++) f[i] = ifac[i];//e^x-1
	f = Mul(Qpow(f, k), ifac[k]);
	for(int i = 0; i <= n; i++) printf("%d ", mul(f[i], fac[i]));
	return 0;
}
