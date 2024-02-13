#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <vector>
using i64 = long long;

constexpr int MAXN = 4e5 + 5;
int n, m;
struct Edge {
  int v, nxt, w;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
  e[++cnt] = {v, head[u], w}; head[u] = cnt;
}

int dfn[MAXN], low[MAXN], tim, cut[MAXN], id[MAXN];

void tarjan(int u, int fa) {
  dfn[u] = low[u] = ++tim;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = std::min(low[u], low[v]);
      if (low[v] > dfn[u])
        cut[i] = cut[i^1] = 1;
    } else {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
}
std::vector<int> ans;
int vis[MAXN];
int ct;
bool dfs(int u) {
  vis[u] = 1;
  if (u == e[ct^1].v) {
    ans.push_back(u);
    return true;
  }
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (vis[v] || i == ct || (i^1) == ct)
      continue;
    if (dfs(v)) {
      ans.push_back(u);
      return true;
    }
  }
  return false;
}
void work() {
  std::cin >> n >> m;
  std::memset(head, 0x00, (n+1) * sizeof(int));
  std::memset(dfn, 0x00, (n+1) * sizeof(int));
  std::memset(vis, 0x00, (n+1) * sizeof(int));
  tim = 0;
  cnt = 1;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    addedge(u, v, w);
    addedge(v, u, w);
  }
  std::memset(cut, 0x00, (cnt+1) * sizeof(int));
  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      tarjan(i, 0);
  for (int i = 2; i <= cnt; i++)
    id[i] = i;
  std::sort(id + 2, id + cnt + 1, [](int x, int y) {return e[x].w < e[y].w;});
  ct = -1;
  for (int i = 2; i <= cnt; i++)
    if (!cut[id[i]]) {
      ct = id[i];
      break;
    }
  ans.clear();
  dfs(e[ct].v);
  std::cout << e[ct].w << ' ' << ans.size() << '\n';
  for (auto v : ans)
    std::cout << v << ' ';
  std::cout << '\n';
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
