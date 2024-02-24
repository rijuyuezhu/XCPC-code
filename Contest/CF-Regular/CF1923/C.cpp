#include <iostream>
#include <vector>
#include <algorithm>
using i64 = long long;

void work() {
  i64 n, q;
  std::cin >> n >> q;
  std::vector<i64> c(n+1), s1(n+1), c1(n+1);
  for (i64 i = 1; i <= n; i++) {
    std::cin >> c[i];
    s1[i] = s1[i-1] + c[i] - 1;
    c1[i] = c1[i-1] + (c[i] == 1 ? 1 : 0);
  }
  while (q--) {
    i64 l, r;
    std::cin >> l >> r;
    if (l < r) {
      if (s1[r] - s1[l-1] >= c1[r] - c1[l-1])
        std::cout << "YES" << '\n';
      else
        std::cout << "NO" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
