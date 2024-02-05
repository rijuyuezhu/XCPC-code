#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 2e5 + 5;
constexpr i64 LINF = 1e18;
i64 n, a[MAXN], s[MAXN];
int que[MAXN], hd, tl;
i64 dp[MAXN];
bool check(i64 V) {
  hd = 1; tl = 0;
  que[++tl] = 0;
  dp[0] = 0;
  for (int i = 1; i <= n+1; i++) {
    while (hd <= tl && (s[i-1] - s[que[hd]] > V))
      hd++;
    dp[i] = dp[que[hd]] + a[i];
    while (hd <= tl && (dp[que[tl]] > dp[i]))
      --tl;
    que[++tl] = i;
  }
  return dp[n+1] <= V;
}
void work() {
  std::cin >> n;
  s[0] = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    s[i] = s[i-1] + a[i];
  }
  a[n+1] = 0; s[n+1] = s[n];
  i64 L = 0, R = s[n], ans = -1;
  while (L <= R) {
    i64 M = (L + R) >> 1;
    if (check(M)) {
      ans = M;
      R = M - 1;
    } else {
      L = M + 1;
    }
  }
  std::cout << ans << '\n';
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
