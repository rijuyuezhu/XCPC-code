#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 1e5 + 5;
int n;
bool sel[MAXN];
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    sel[i] = 0;
  for (int i = 1; i <= n; i++) {
    if (sel[i])
      continue;
    std::cout << i << ' ';
    sel[i] = 1;
    int now = i;
    while(now * 2 <= n) {
      std::cout << now * 2 << ' ';
      sel[now * 2] = 1;
      now *= 2;
    }
  }
  std::cout << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--)
    work();
  return 0;
}
