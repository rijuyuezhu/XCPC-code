#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using i64 = long long;
constexpr int MAXN = 5e5 + 5;
constexpr int MAXM = 4e6 + 5;
std::vector<std::vector<int> > dcc;
int n, m;
struct Edge {
  int v, nxt;
}e[MAXM];
int cnt, head[MAXN];
void addedge(int u, int v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}
int dfn[MAXN], low[MAXN], tim, cut[MAXN];
std::stack<int> stk;

void tarjan(int u, int rt) {
  dfn[u] = low[u] = ++tim; stk.push(u);
  if (u == rt && head[u] == 0) {
    std::vector<int> newdcc;
    newdcc.push_back(u);
    dcc.push_back(newdcc);
    return ;
  }
  int ch = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!dfn[v]) {
      tarjan(v, rt);
      low[u] = std::min(low[u], low[v]);
      ch++;
      if (low[v] >= dfn[u]) {
        if (u != rt || ch >= 2)
          cut[u] = 1;
        std::vector<int> newdcc;
        int t;
        do {
          t = stk.top(); stk.pop();
          newdcc.push_back(t);
        } while(t != v);
        newdcc.push_back(u);
        dcc.push_back(newdcc);
      }
    } else {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    if (u == v)
      continue;
    addedge(u, v);
    addedge(v, u);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      tarjan(i, i);
  std::cout << dcc.size() << '\n';
  for (const auto &vec : dcc) {
    std::cout << vec.size() << ' ';
    for (auto v : vec)
      std::cout << v << ' ';
    std::cout << '\n';
  }

  return 0;
}
