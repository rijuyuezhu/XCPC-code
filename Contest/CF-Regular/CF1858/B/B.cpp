#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXM = 1e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, m, d;
int s[MAXM], T[MAXM], ans;
void work() {
  std::cin >> n >> m >> d;
  for (int i = 1; i <= m; i++)
    std::cin >> s[i];
  ans = INF;
  T[0] = 0;
  s[0] = 1-d;
  s[m+1] = n+1;
  for (int i = 1; i <= m+1; i++) {
    T[i] = T[i-1] + (s[i] - s[i-1] - 1) / d + (i <= m);
  }
  for (int i = 1; i <= m; i++)
    ans = std::min(ans, T[i-1] + T[m+1] - T[i+1] + (s[i+1] - s[i-1] - 1) / d + (i < m));
  int tot = 0;
  for (int i = 1; i <= m; i++)
    if (T[i-1] + T[m+1] - T[i+1] + (s[i+1] - s[i-1]-1) / d + (i < m) == ans)
      tot++;
  std::cout << ans << ' ' << tot << '\n';
  // for (int i = 0; i <= m+1; i++)
  //   std::cout << T[i] << ' ';
  // std::cout << '\n';
  // for (int i = 1; i <= m; i++)
  //  std::cout << (T[i-1] + T[m+1] - T[i+1] + (s[i+1] - s[i-1]) / d + (i < m)) << ' ';
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
