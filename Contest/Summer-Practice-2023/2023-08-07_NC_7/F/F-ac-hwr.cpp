#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using i64 = long long;
constexpr int MAXN = (1 << 18) + 5, P = 998244353, BAS = 1 << 18;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
  int v;
  mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1LL * a.v * b.v % P;}
mint qpow(mint a, int n = P-2) {
  mint ret = 1;
  for (; n; n >>= 1, a = a * a)
    if (n & 1)
      ret = ret * a;
  return ret;
}

using poly = vector<mint>;
mint _g[MAXN], inv[MAXN], fac[MAXN], ifac[MAXN];
int tr[MAXN], tf;
poly Rez(poly f, int n) {
  f.resize(n); return f;
}
void init() {
  _g[0] = 1; _g[1] = qpow(3, (P-1) / BAS);
  for (int i = 2; i < BAS; i++) _g[i] = _g[i-1] * _g[1];
  inv[1] = 1; for (int i = 2; i < MAXN; i++) inv[i] = (P-P/i) * inv[P % i];
  fac[0] = 1; for (int i = 1; i < MAXN; i++) fac[i] = fac[i-1] * i;
  ifac[0] = 1; for (int i = 1; i < MAXN; i++) ifac[i] = ifac[i-1] * inv[i];
}
int glim(int n) {
  int lim = 1; for (; lim < n; lim <<= 1);
  return lim;
}
void tpre(int lim) {
  if (lim == tf) return;
  tf = lim;
  for (int i = 0; i < lim; i++)
    tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void DFT(poly &f, int lim) {
  tpre(lim); if ((int)f.size() < lim) f.resize(lim);
  for (int i = 0; i < lim; i++) if (i < tr[i]) swap(f[i], f[tr[i]]);
  for (int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
    for (int i = 0; i < lim; i += l)
      for (int j = i; j < i + k; j++) {
        mint tt = f[j+k] * _g[BAS / l * (j-i)];
        f[j+k] = f[j] - tt;
        f[j] = f[j] + tt;
      }
}
void IDFT(poly &f, int lim) {
  DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
  for (int i = 0; i < lim; i++) f[i] = f[i] * inv[lim];
}
poly Mul(poly f, poly g) {
  int n = f.size() + g.size() - 1, lim = glim(n);
  DFT(f, lim); DFT(g, lim);
  for (int i = 0; i < lim; i++) f[i] = f[i] * g[i];
  IDFT(f, lim); f.resize(n); return f;
}
poly Mns(poly f, poly g) {
  f.resize(max(f.size(), g.size()));
  for (int i = 0; i < (int)g.size(); i++) f[i] = f[i] - g[i];
  return f;
}
poly Deriv(poly f) {
  for (int i = 1; i < (int)f.size(); i++) f[i-1] = f[i] * i;
  f.pop_back(); return f;
}
poly Integ(poly f) {
  f.push_back(0);
  for (int i = f.size()-1; i >= 1; i--) f[i] = f[i-1] * inv[i];
  f[0] = 0; return f;
}
poly Inv(poly f) {
  if (f.size() == 1) return poly(1, qpow(f[0]));
  int n = f.size(), lim = glim(n+n);
  poly g = f; g.resize((n+1) / 2); g = Inv(g);
  DFT(f, lim); DFT(g, lim);
  for (int i = 0; i < lim; i++)
    f[i] = g[i] * (2 - f[i] * g[i]);
  IDFT(f, lim); f.resize(n); return f;
}
poly Ln(const poly &f) {
  poly ans = Integ(Mul(Inv(f), Deriv(f)));
  ans.resize(f.size());
  return ans;
}
poly Exp(poly f) {
  if (f.size() == 1) return poly(1, 1);
  int n = f.size(), lim = glim(n+n);
  poly g = f; g.resize((n+1) / 2); g = Exp(g); g.resize(n);
  f = Mns(f, Ln(g)); f[0] = f[0] + 1;
  DFT(f, lim); DFT(g, lim);
  for (int i = 0; i < lim; i++) f[i] = f[i] * g[i];
  IDFT(f, lim); f.resize(n); return f;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, k;
  cin >> n >> m >> k;
  init();
  poly f(k+1);
  f[0] = 1;
  for (int i = 1; i <= k; i++)
    f[i] = f[i-1] * (n-i+1) * inv[i];
  for (int i = 1; i <= k; i += 2)
    f[i] = 0;
  poly g = Ln(f);
  for(int i = 0; i < (int)g.size(); i++)
    g[i] = g[i] * m;
  f = Exp(g);
  cout << (f[k] * qpow(2, m)).v << '\n';
  return 0;
}
