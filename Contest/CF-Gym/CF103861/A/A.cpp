#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 2e5 + 5;

int n;
struct Edge {
  int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
int dep[MAXN], siz[MAXN];
void addedge(int u, int v) {
  e[++cnt] = {v, head[u]}; head[u] = cnt;
}

void dfs(int u, int F) {
  dep[u] = dep[F] + 1;
  siz[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == F)
      continue;
    dfs(v, u);
    siz[u] += siz[v];
  }
}
void work() {
  std::cin >> n;
  cnt = 0;
  for (int i = 1; i <= n; i++)
    head[i] = 0;
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    addedge(u, v);
    addedge(v, u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++)
    std::cout << dep[i] << ' ' << (n - siz[i] + 1) << '\n';
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
