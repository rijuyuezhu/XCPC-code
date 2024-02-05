#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;

constexpr int MAXN = 2e5 + 5;
int n, k;
struct Edge {
  int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
  e[++cnt] = {v, head[u]}; head[u] = cnt;
}
int dep[MAXN], son[MAXN], fa[MAXN], udep[MAXN];
void dfs1(int u) {
  int maxd = -1;
  dep[u] = 0;
  udep[u] = udep[fa[u]] + 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u])
      continue;
    dfs1(v);
    if (dep[v] > maxd) {
      maxd = dep[v];
      son[u] = v;
    }
    dep[u] = std::max(dep[u], dep[v] + 1);
  }
}

int top[MAXN];
void dfs2(int u, int tp) {
  top[u] = tp;
  if (son[u])
    dfs2(son[u], tp);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u] || v == son[u])
      continue;
    dfs2(v, v);
  }
}
bool cmp(int x, int y) {return x > y;}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k;
  for (int i = 2; i <= n; i++) {
    std::cin >> fa[i];
    addedge(fa[i], i);
  }
  dfs1(1);
  dfs2(1, 1);
  std::vector<int> can;
  for (int i = 1; i <= n; i++)
    if (dep[i] == 0) {
      if (top[i] == 1)
        can.push_back(dep[top[i]]);
      else
        can.push_back(dep[top[i]] - udep[fa[top[i]]] + 2);
    }
  // for (auto v : can)
  //   std::cout << v << '\n';
  sort(can.begin(), can.end(), cmp);
  int tot = std::min(k + 1, (int)can.size());
  int ans = 2 * (n - 1);
  for (int i = 0; i < tot; i++)
    ans -= std::max(0, can[i]);
  std::cout << ans << '\n';
  return 0;
}
