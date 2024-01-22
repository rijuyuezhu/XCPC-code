#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 3e5 + 5;
int c[MAXN], n;

i64 C2(i64 n) { return n * (n - 1) / 2; }
i64 C3(i64 n) { return n * (n - 1) * (n - 2) / 6;}
void work() {
  std::cin >> n;
  for (int i = 0; i <= n; i++)
    c[i] = 0;
  for (int i = 1; i <= n; i++) {
    int v;
    std::cin >> v;
    c[v]++;
  }
  i64 ans = 0;
  i64 pre = 0;
  for (int i = 0; i <= n; i++) {
    if (c[i] >= 2)
      ans += pre * C2(c[i]);
    if (c[i] >= 3)
      ans += C3(c[i]);
    pre += c[i];
  }
  std::cout << ans << '\n';
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
