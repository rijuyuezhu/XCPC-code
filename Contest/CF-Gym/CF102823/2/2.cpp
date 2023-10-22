#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using i64 = long long;
constexpr int P = 998244353;
constexpr int MAXN = (1 << 18) + 5, BAS = 1 << 18;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
  int v;
  mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1LL * a.v * b.v % P;}
mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if (n & 1) ret = ret * a; return ret;}
namespace Poly {
  using poly = std::vector<mint>;
  int tr[MAXN], tf;
  mint _g[MAXN], inv[MAXN], fac[MAXN], ifac[MAXN];
  void init() {
    _g[0] = 1; _g[1] = qpow(3, (P-1) / BAS);
    for (int i = 2; i < BAS; i++) _g[i] = _g[i-1] * _g[1];
    inv[1] = 1; for (int i = 2; i < MAXN; i++) inv[i] = (P - P / i) * inv[P % i];
    fac[0] = 1; for (int i = 1; i < MAXN; i++) fac[i] = fac[i-1] * i;
    ifac[0] = 1; for (int i = 1; i < MAXN; i++) ifac[i] = ifac[i-1] * inv[i];
  }
  int glim(int n) {
    int lim = 1; for(; lim < n; lim <<= 1);
    return lim;
  }
  void tpre(int lim) {
    if (lim == tf) return;
    tf = lim; for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
  }
  void DFT(poly &f, int lim) {
    tpre(lim); if ((int)f.size() < lim) f.resize(lim);
    for (int i = 0; i < lim; i++) if (i < tr[i]) std::swap(f[i], f[tr[i]]);
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
  poly Mul(poly f, poly g, int nn) {
    int n = f.size() + g.size() - 1, lim = glim(n);
    DFT(f, lim); DFT(g, lim);
    for (int i = 0; i < lim; i++) f[i] = f[i] * g[i];
    IDFT(f, lim); f.resize(nn); return f;
  }
  poly Pow(poly a, int k) {
    int n = a.size();
    poly ret(n); ret[0] = 1;
    for (; k; k >>= 1, a = Mul(a, a, n))
      if (k & 1)
        ret = Mul(ret, a, n);
    return ret;
  }
}
using namespace Poly;
int n, L, m;
void work(int te) {
  std::cin >> n >> L >> m;
  poly f0(n+1), g(n+1), res;
  for (int i = 1; i <= n; i++)
    std::cin >> f0[i].v;
  for (int i = 0; i < L; i++)
    g[i] = 1;
  g = Pow(g, m);
  reverse(g.begin(), g.begin()+n+1);
  res = Mul(f0, g);
  assert((int)res.size() >= 2 * n);
  std::cout << "Case " << te << ": ";
  for (int i = 1; i <= n; i++)
    std::cout << res[i+n].v << ' ';
  std::cout << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init();
  int T;
  std::cin >> T;
  for (int i = 1; i <= T; i++)
    work(i);
  return 0;
}
