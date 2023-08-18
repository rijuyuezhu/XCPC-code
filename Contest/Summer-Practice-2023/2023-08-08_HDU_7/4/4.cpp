#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int M = 31622;
i64 fe[M+1], fo[M+1];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for (i64 i = 1; i <= M; i++) {
    fo[i] = i * i + 2 * i;
    fe[i] = i * i + 3 * i;
  }
  int T;
  std::cin >> T;
  while (T--) {
    i64 n;
    std::cin >> n;
    int L = 1, R = M / 2, ans = M; // odd
    while (L <= R) {
      int m = (L + R) >> 1;
      if (fo[2 * m - 1] >= n) {
        ans = std::min(ans, 2 * m - 1);
        R = m - 1;
      } else {
        L = m + 1;
      }
    }
    L = 1, R = M / 2;
    while (L <= R) {
      int m = (L + R) >> 1;
      if (fe[2 * m] >= n) {
        ans = std::min(ans, 2 * m);
        R = m - 1;
      } else {
        L = m + 1;
      }
    }
    std::cout << ans << '\n';
  }
  return 0;
}
