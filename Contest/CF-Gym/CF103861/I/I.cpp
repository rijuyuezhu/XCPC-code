#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
int v, n;
void work() {
  std::cin >> n;
  int a1 = 0, a2 = 0, a3 = 0;
  for (int i = 1; i <= n; i++) {
    int v;
    std::cin >> v;
    if (v > 1)
      a1++;
    else if (v == 1)
      a2++;
    else
      a3++;
  }
  std::cout << (1LL * a2 * (a1 + a3) + 1LL * a1 * a3 + 1LL * a2 * (a2 - 1) / 2) << '\n';
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
