#include <iostream>
#include <algorithm>
using i64 = long long;
using pii = std::pair<int, int>;
constexpr int MAXN = 2e5 + 5;
int n;
pii x[MAXN];
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> x[i].first;
  for (int i = 1; i <= n; i++)
    std::cin >> x[i].second;
  std::sort(x + 1, x + 1 + n);
  for (int i = 1; i <= n; i++)
    std::cout << x[i].first << ' ';
  std::cout << '\n';
  for (int i = 1; i <= n; i++)
    std::cout << x[i].second << ' ';
  std::cout << '\n';
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
