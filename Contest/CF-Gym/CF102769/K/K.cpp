#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
std::vector<int> G[MAXN];
int n;
int f[MAXN];
int ans;
void dfs(int u, int dep, int rt) {
  f[u] = 0;
  for (auto v : G[u]) {
    dfs(v, dep + 1, rt);
    if (dep < f[v] + 1) {
      fprintf(stderr, "at %d, %d\n", u, v);
      ans -= f[v] + 1 - dep;
    }
    f[u] = std::max(f[u], f[v] + 1);
  }
  if (u != rt && dep < f[u])
    ans += f[u] - dep;
}
void work(int te) {
  std::cin >> n;
  ans = 2 * n - 2;
  for (int i = 1; i <= n; i++) {
    G[i].clear();
  }
  for (int i = 2; i <= n; i++) {
    int f;
    std::cin >> f;
    G[f].push_back(i);
  }
  dfs(1, 0, 1);
  std::cout << "Case #" << te << ": " << ans << '\n';
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
