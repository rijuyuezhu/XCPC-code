#include <iostream>
#include <algorithm>
#include <cmath>
using i64 = long long;


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    i64 x, a, b, cnt = 0;
    std::cin >> x >> a >> b;
    while (1) {
      i64 nx1 = x-1, nx2 = (x + a) / 2, nx3 = i64(std::floor(std::sqrt(x + b)));
      i64 nx = std::min(std::min(nx1, nx2), nx3);
      if (nx < x - 1) {
        cnt++;
        x = nx;
      } else 
        break;
    }
    std::cout << cnt + x << '\n';
  }
  return 0;
}
