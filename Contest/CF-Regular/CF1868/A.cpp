#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 2e5 + 5;
int n, m;
int p[MAXN];
void right() {
  int x = p[m-1];
  for (int i = m-1; i >= 1; i--)
    p[i] = p[i-1];
  p[0] = x;
}
void work() {
  std::cin >> n >> m;
  if (m == 1) {
    std::cout << 0 << '\n';
    for (int i = 1; i <= n; i++)
      std::cout << 0 << '\n';
    return ;
  }
  for (int i = 0; i < m; i++)
    p[i] = i;
  if (n >= m-1) {
    std::cout << m << '\n';
    for (int i = 1; i < m; i++) {
      right();
      for (int j = 0; j < m; j++)
        std::cout << p[j] << ' ';
      std::cout << '\n';
    }
    for (int i = m; i <= n; i++) {
      for (int j = 0; j < m; j++)
        std::cout << p[j] << ' ';
      std::cout << '\n';
    }
  } else {
    std::cout << n+1 << '\n';
    for (int i = 1; i <= n; i++) {
      right();
      for (int j = 0; j < m; j++)
        std::cout << p[j] << ' ';
      std::cout << '\n';
    }
  }
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
