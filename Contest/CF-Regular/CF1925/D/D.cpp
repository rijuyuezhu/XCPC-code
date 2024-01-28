#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 2e5 + 10;
constexpr int P = 1e9 + 7;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
  int v;
  mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return MOD(1LL * a.v * b.v % P);}
mint qpow(mint a, int n=P-2) {
  mint ret = 1;
  for (; n; n >>= 1, a = a * a)
    if (n & 1)
      ret = ret * a;
  return ret;
}
mint fac[MAXN], ifac[MAXN];
void init(int N) {
  fac[0] = 1;
  for (int i = 1; i <= N; i++)
    fac[i] = fac[i-1] * i;
  ifac[N] = qpow(fac[N]);
  for (int i = N-1; i >= 0; i--)
    ifac[i] = ifac[i+1] * (i+1);
}
mint C(int n, int m) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  return fac[n] * ifac[m] * ifac[n-m];
}
void work() {
  int n, m, k;
  mint c1 = 0, c2 = 0, s1 = 0, s2 = 0, p = 0;
  std::cin >> n >> m >> k;
  p = qpow(C(n, 2));
  c2 = m;
  for (int i = 1; i <= m; i++) {
    int u, v, f;
    std::cin >> u >> v >> f;
    c1 = c1 + f;
  }
  for (int t = 0; t <= k; t++) {
    mint factor = C(k, t) * qpow(p, t) * qpow(mint(1)-p, k-t);
    s1 = s1 + factor * mint(t);
    s2 = s2 + factor * C(t, 2);
  }
  std::cout << (c1 * s1 + c2 * s2).v << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  init(2e5 + 5);
  while (T--)
    work();
  return 0;
}
