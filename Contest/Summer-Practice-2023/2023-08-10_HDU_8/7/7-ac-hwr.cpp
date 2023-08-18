#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
int n, m, k, upto[MAXN];
int getup(int x) {
  return x == upto[x] ? x : upto[x] = getup(upto[x]);
}
void work() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    upto[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    if (getup(u) != getup(v))
      upto[getup(u)] = getup(v);
  }
  std::cin >> k;
  int c = -1, flag = 1;
  for (int i = 1; i <= k; i++) {
    int t;
    std::cin >> t;
    if (c == -1 || c == getup(t))
      c = getup(t);
    else
      flag = 0;
  }
  std::cout << (flag ? "YES" : "NO") << '\n';
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
