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
const int MAXN = (1 << 18) + 5, P = 998244353, BAS = 1 << 18;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n=P-2) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
namespace Poly {
	typedef vector<int> poly;
	int _g[MAXN], tr[MAXN], tf, inv[MAXN], fac[MAXN], ifac[MAXN];
	poly Rsz(poly f, int n) {
		f.resize(n); return f;
	}
	void init() {
		_g[0] = 1; _g[1] = qpow(3, (P-1) / BAS);
		for(int i = 2; i < BAS; i++) _g[i] = mul(_g[i-1], _g[1]);
		inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
		fac[0] = 1; for(int i = 1; i < MAXN; i++) fac[i] = mul(fac[i-1], i);
		ifac[0] = 1; for(int i = 1; i < MAXN; i++) ifac[i] = mul(ifac[i-1], inv[i]);
	}
	int glim(int n) {
		int lim = 1; for(; lim < n; lim <<= 1);
		return lim;
	}
	void tpre(int lim) {
		if(lim == tf) return;
		tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
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
	poly Mul(poly f, poly g) {
		int n = f.size() + g.size() - 1, lim = glim(n);
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
		IDFT(f, lim); f.resize(n); return f;
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
	poly Deriv(poly f) {
		for(int i = 1; i < (int)f.size(); i++) f[i-1] = mul(f[i], i);
		f.pop_back(); return f;
	}
	poly Integ(poly f) {
		f.push_back(0);
		for(int i = f.size()-1; i >= 1; i--) f[i] = mul(f[i-1], inv[i]);
		f[0] = 0; return f;
	}
	poly Inv(poly f) {
		if(f.size() == 1) return poly(1, qpow(f[0]));
		int n = f.size(), lim = glim(n+n);
		poly g = f; g.resize((n+1)/2); g = Inv(g);
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(g[i], mns(2, mul(f[i], g[i])));
		IDFT(f, lim); f.resize(n); return f;
	}
	poly Ln(const poly& f) {
		poly ans = Integ(Mul(Inv(f), Deriv(f)));
		ans.resize(f.size());
		return ans;
	}
	poly Exp(poly f) {
		if(f.size() == 1) return poly(1, 1);
		int n = f.size(), lim = glim(n+n);
		poly g = f; g.resize((n+1)/2); g = Exp(g); g.resize(n);//careful
		f = Mns(f, Ln(g)); f[0]++;
		DFT(f, lim); DFT(g, lim);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
		IDFT(f, lim); f.resize(n); 
		return f;
	}
	poly Rev(poly f) {
		reverse(f.begin(), f.end());
		return f;
	}
	poly Div(const poly& f, const poly& g) {
		if(f.size() < g.size()) return poly();
		int n = f.size() - g.size() + 1;
		poly ans = Mul(Rev(f), Inv(Rsz(Rev(g), n)));//careful the Rsz
		ans.resize(n);
		return Rev(ans);
	}
	poly Mod(const poly& f, const poly& g) {
		poly ans = Mns(f, Mul(Div(f, g), g));
		ans.resize(g.size()-1);
		return ans;
	}
	namespace Fastcalc {
		#define ls p << 1
		#define rs p << 1 | 1
		poly h[MAXN << 2];
		poly TMul(poly f, poly g) {
			int n = f.size(), m = g.size(), lim = glim(n);
			g = Rev(g);
			DFT(f, lim); DFT(g, lim);
			for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
			IDFT(f, lim);
			poly T(n-m+1);
			for(int i = 0; i < n-m+1; i++) T[i] = f[i+m-1];
			return T;
		}
		void build(int p, int l, int r, const poly& a) {
		 	if(l == r) {
				h[p].resize(2); h[p][0] = 1; h[p][1] = mns(0, a[l]);
				return;
			}
			int m = (l + r) >> 1;
			build(ls, l, m, a); build(rs, m+1, r, a);
			h[p] = Mul(h[ls], h[rs]);
		}
		void calc1(int p, int l, int r, poly& ans, const poly& now) {
			if(l == r) {
				ans[l] = now[0];
				return ;
			}
			int m = (l + r) >> 1;
			calc1(ls, l, m, ans, TMul(now, h[rs]));
			calc1(rs, m+1, r, ans, TMul(now, h[ls]));
		}
		poly Eva(poly F, poly a) {
			int n = F.size(), m = a.size();
			n = max(n, m); F.resize(n); a.resize(n);
			build(1, 0, n-1, a);
			F.resize(2 * n + 1);
			calc1(1, 0, n-1, a, TMul(F, Inv(h[1])));
			a.resize(m);
			return a;
		}
		poly calc2(int p, int l, int r, const poly& Y) {
			if(l == r) return poly(1, Y[l]);
			int m = (l + r) >> 1;
			return Pls(Mul(calc2(ls, l, m, Y), h[rs]), Mul(calc2(rs, m+1, r, Y), h[ls]));
		}
		poly Ins(poly X, poly Y) {
			int n = X.size(); if(!n) return poly();
			build(1, 0, n-1, X);
			poly F = Deriv(Rev(h[1])); 
			F.resize(2 * n + 1); 
			calc1(1, 0, n-1, X, TMul(F, Inv(h[1])));
			for(int i = 0; i < n; i++) Y[i] = mul(Y[i], qpow(X[i]));
			return Rev(calc2(1, 0, n-1, Y));
		}
		#undef ls
		#undef rs
	}
}
using namespace Poly;
int main() {
	init();
	int n = read();
	poly X(n), Y(n);
	for(int i = 0; i < n; i++) X[i] = read(), Y[i] = read();
	poly ans = Fastcalc::Ins(X, Y);
	for(int i = 0; i < (int)ans.size(); i++) printf("%d ", ans[i]);
	return 0;
}
