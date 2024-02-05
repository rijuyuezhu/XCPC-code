#include <iostream>
#include <algorithm>
using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    i64 n, m;
    std::cin >> n >> m;
    if (m % 2 == 0)
      std::cout << (n * m / 2) << '\n';
    else
      std::cout << (n * (m - 1) / 2) << '\n';
  }
  return 0;
}
