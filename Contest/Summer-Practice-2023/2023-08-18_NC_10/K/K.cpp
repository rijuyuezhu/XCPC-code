#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  std::cout << std::fixed << std::setprecision(15);
  if (n == 1)
    std::cout << 1.0 << '\n';
  else {
    std::cout << std::pow(2.0 / n, 1.0 * m) << '\n';
  }
  return 0;
}
