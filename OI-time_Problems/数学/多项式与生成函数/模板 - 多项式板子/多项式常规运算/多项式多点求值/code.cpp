#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<ctime>
#include<iostream>
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
const int MAXN = 3e5 + 5;
const int P = 998244353, BAS = 1 << 18;
typedef vector<int> Poly;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int _g[MAXN], tr[MAXN], tf, inv[MAXN];
void init() {
	_g[0] = 1; _g[1] = qpow(3, (P-1) / BAS);
	for(int i = 2; i < BAS; i++) _g[i] = mul(_g[i-1], _g[1]);
	inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
}
int getlim(int n) {
	int lim = 1; for(; lim < n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return; 
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void DFT(Poly& f, int lim) {
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
void IDFT(Poly& f, int lim) {
	DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
	for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
}
Poly Inv(Poly f) {
	int n = f.size();
	if(n == 1) return Poly(1, qpow(f[0], P-2));
	Poly g = f; g.resize((n+1)/2); g = Inv(g);
	int lim = getlim(n+n);
	DFT(f, lim); DFT(g, lim);
	for(int i = 0; i < lim; i++) f[i] = mul(g[i], mns(2, mul(f[i], g[i])));
	IDFT(f, lim); f.resize(n);
	return f;
}
Poly Mul(Poly f, Poly g) {
	int n = f.size() + g.size() - 1;
	int lim = getlim(n);
	DFT(f, lim); DFT(g, lim);
	for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
	IDFT(f, lim); f.resize(n);
	return f;
}
Poly TMul(Poly f, Poly g) {//g is constant
	int n = f.size(), m = g.size();
	if(n <= 64) {
		for(int i = 0; i < n-m+1; i++) {
			int ret = 0;
			for(int j = 0; j < m; j++) ret = pls(ret, mul(f[i+j], g[j]));
			f[i] = ret;
		}
		f.resize(n-m+1);
		return f;
	}
	reverse(g.begin(), g.end());
	int lim = getlim(n);
	DFT(f, lim); DFT(g, lim);
	for(int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
	IDFT(f, lim);
	Poly T(n-m+1);
	for(int i = 0; i < n-m+1; i++) T[i] = f[i+m-1];
	return T;
}
int n, m;
Poly f, a, t[MAXN << 2];
#define ls p << 1
#define rs p << 1 | 1
void build(int p, int l, int r, Poly& a) {
	if(l == r) {
		t[p].resize(2);
		t[p][0] = 1; t[p][1] = mns(0, a[l]);
		return ;
	}
	int m = (l + r) >> 1;
	build(ls, l, m, a); build(rs, m+1, r, a);
	t[p] = Mul(t[ls], t[rs]);
}
void calc(int p, int l, int r, Poly& a) {
	if(l == r) {
		a[l] = t[p][0];
		return ;
	}
	int m = (l + r) >> 1;
	swap(t[ls], t[rs]);
	t[ls] = TMul(t[p], t[ls]);
	t[rs] = TMul(t[p], t[rs]);
	calc(ls, l, m, a);
	calc(rs, m+1, r, a);
}
#undef ls
#undef rs
Poly solve(Poly f, Poly a) {
	int n = f.size(), m = a.size();
	n = max(n, m); f.resize(n); a.resize(n);
	build(1, 0, n-1, a);
	f.resize(2 * n + 1); 
	t[1] = TMul(f, Inv(t[1]));
	calc(1, 0, n-1, a);
	a.resize(m);
	return a;
}
int main() {
	init();
	n = read()+1, m = read();
	f.resize(n); a.resize(m);
	for(int i = 0; i < n; i++) f[i] = read();
	for(int i = 0; i < m; i++) a[i] = read();
	a = solve(f, a);
	for(int i = 0; i < m; i++) printf("%d\n", a[i]);
	return 0;
}
