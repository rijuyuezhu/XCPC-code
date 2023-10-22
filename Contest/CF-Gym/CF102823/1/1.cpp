#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 1e5 + 5;
int n, m, a[MAXN], b[MAXN];
i64 ans;
void work(int te) {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  for (int i = 1; i <= m; i++) 
    std::cin >> b[i];
  int p = 1, q = 1;
  ans = 0;
  for (int i = 1; i <= n + m; i++) {
    if (q > m || (p <= n && a[p] > b[q]))
      ans += 1LL * i * a[p++];
    else
      ans += 1LL * i * b[q++];
  }
  std::cout << "Case " << te << ": "<< ans << '\n';
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
