#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
constexpr int P = 1e9 + 7;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
  int v;
  mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1LL * a.v * b.v % P;}
mint qpow(mint a, int n) {
  mint ret = 1;
  for(; n; n >>= 1, a = a * a)
    if (n & 1)
      ret = ret * a;
  return ret;
}
mint fac[MAXN];
void init(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = fac[i-1] * i;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init(1e6+3);
  int T;
  std::cin >> T;
  while (T--) {
    int n, k;
    std::cin >> n >> k;
    std::cout << (fac[n] * fac[k-1] * qpow(k, n-k)).v << '\n';
  }
  return 0;
}
