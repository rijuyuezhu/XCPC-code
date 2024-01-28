#include <iostream>
#include <algorithm>
using i64 = long long;

void work() {
  int n, k;
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < k; j++)
      std::cout << char('a' + j);
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
