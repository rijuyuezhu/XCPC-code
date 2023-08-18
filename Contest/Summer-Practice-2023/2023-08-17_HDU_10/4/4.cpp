#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int P = 998244353;
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

void work() {
  int n;
  std::cin >> n;
  if (n == 1)
    std::cout << 0 << '\n';
  else
    std::cout << ((2 * mint(n) - 1) * qpow(3, P-2)).v << '\n';
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
