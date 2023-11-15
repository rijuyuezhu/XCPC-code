#include <iostream>
#include <algorithm>
#include <cassert>
using i64 = long long;
i64 n, k;

i64 qpow(i64 a, i64 n) {
  i64 ret = 1;
  for (; n; n >>= 1) {
    if (n & 1) {
      ret *= a;
      if (ret > 2e9)
        return 2e9;
    }
    a *= a;
    if (a > 2e9)
      return 2e9;
  }
  return ret;
}
void work(int te) {
  std::cin >> n >> k;
  i64 ans = 0;
  if (k == 1) {
    ans = n;
  } else {
    assert(k >= 2);
    for (i64 t = 1; ; t++) {
      i64 L = qpow(t, k), R = qpow(t+1, k) - 1;
      R = std::min(R, n);
      if (L > n)
        break;
      if (L > R)
        continue;
      ans += (R / t) - ((L + t - 1) / t) + 1;
    }
  }
  std::cout << "Case #" << te << ": " << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  for (int i = 1; i <= T; i++)
    work(i);
  return 0;
}
