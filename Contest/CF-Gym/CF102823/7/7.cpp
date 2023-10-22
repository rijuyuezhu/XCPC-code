#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, a[MAXN];
int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}
void upd(int &ans, int f) {
  if (a[1] % f == 0) {
    ans = 0;
  } else {
    ans = std::min(ans, f * (a[1] / f + 1) - a[1]);
  }
}
void work(int t) {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  std::sort(a + 1, a + 1 + n);
  int g = 0;
  for (int i = 2; i <= n; i++)
    g = gcd(g, a[i] - a[1]);
  int ans = INF;
  if (g == 0)
    ans = a[1] > 1 ? 0 : 1;
  else {
    for (int i = 2; i * i <= g; i++)
      if (g % i == 0) {
        upd(ans, i);
        upd(ans, g / i);
      }
    if (g > 1)
      upd(ans, g);
  }
  std::cout << "Case " << t << ": " << (ans == INF ? -1 : ans) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  for (int i = 1; i <= T; i++)
    work(i);
  return 0;
}
