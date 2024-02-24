#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;

void work() {
  i64 n, k;
  std::cin >> n >> k;
  std::vector<i64> a(n+1, 0);
  std::vector<i64> v(n+1, 0);
  for (i64 i = 1; i <= n; i++)
    std::cin >> a[i];
  for (i64 i = 1; i <= n; i++) {
    i64 x;
    std::cin >> x;
    v[std::abs(x)] += a[i];
  }
  bool ok = true;
  for (i64 i = 1; i <= n; i++) {
    v[i] += v[i-1];
    if (v[i] > i * k) {
      ok = false;
      break;
    }
  }
  std::cout << (ok ? "YES" : "NO") << '\n';
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
