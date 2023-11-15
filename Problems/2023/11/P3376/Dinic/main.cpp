#include <algorithm>
#include <iostream>
#include <queue>
using i64 = long long;
constexpr int MAXN = 205;
constexpr int MAXM = 10005;
constexpr i64 LINF = 1e18;

int n, m, s, t;
struct Edge {
  int v, nxt;
  i64 w;
}e[MAXM];
int head[MAXN], cur[MAXN], cnt = 1;
void addedge(int u, int v, i64 w) {
  e[++cnt] = {v, head[u], w}; head[u] = cnt;
}

int dep[MAXN];
bool bfs() {
  for (int i = 1; i <= n; i++)
    dep[i] = 0, cur[i] = head[i];
  std::queue<int> que;
  que.push(s); dep[s] = 1;
  while (que.size()) {
    int u = que.front(); que.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (e[i].w && dep[v] == 0) {
        dep[v] = dep[u] + 1;
        que.push(v);
        if (v == t) return 1;
      }
    }
  }
  return 0;
}

i64 dfs(int u, i64 flow) {
  if (u == t)
    return flow;
  i64 rest = flow;
  for (int &i = cur[u]; i && rest; i = e[i].nxt) {
    int v = e[i].v;
    if (e[i].w && dep[v] == dep[u] + 1) {
      i64 flowto = dfs(v, std::min(rest, e[i].w));
      if (!flowto)
        dep[v] = 0;
      e[i].w -= flowto;
      rest -= flowto;
      e[i^1].w += flowto;
    }
  }
  return flow - rest;
}

i64 dinic() {
  i64 maxflow = 0, nowflow = 0;
  while (bfs()) {
    while ((nowflow = dfs(s, LINF)) > 0)
      maxflow += nowflow;
  }
  return maxflow;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> s >> t;
  cnt = 1;
  for (int i = 1; i <= m; i++) {
    int u, v; i64 w;
    std::cin >> u >> v >> w;
    addedge(u, v, w);
    addedge(v, u, 0);
  }
  i64 maxflow = dinic();
  std::cout << maxflow << '\n';
  return 0;
}
