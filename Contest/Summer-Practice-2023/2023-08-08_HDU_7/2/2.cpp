#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int P = 998244353;

void work() {
  int n, cnt = 0;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    std::cin >> a;
    if (a == 1)
      ++cnt;
  }
  if (cnt == n) {
    if (n & 1)
      std::cout << 1 << '\n';
    else 
      std::cout << 0 << '\n';
  } else {
    std::cout << 499122177 << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
