#include <iostream>
#include <algorithm>
using i64 = long long;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    int x, n;
    std::cin >> x >> n;
    int lim = x / n;
    int ans = 1;
    for (int i = 1; 1LL * i * i <= x; i++) {
      if (x % i == 0) {
        if (i <= lim)
          ans = std::max(ans, i);
        if (x / i <= lim)
          ans = std::max(ans, x / i);
      }
    }
    std::cout << ans << '\n';
  }
  return 0;
}
