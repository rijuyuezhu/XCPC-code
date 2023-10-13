#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <stack>
constexpr int MAXN = 1e5 + 5;
int n, m, s, ind[MAXN], outd[MAXN], del[MAXN];
std::vector<int> G[MAXN];
std::stack<int> st;
void fail() {
  std::cout << "No" << '\n';
  exit(0);
}

void dfs(int u) {
  for (int i = del[u]; i < (int)G[u].size(); i = del[u]) {
    del[u] = i + 1;
    dfs(G[u][i]);
  }
  st.push(u);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    ind[v]++;
    outd[u]++;
    G[u].push_back(v);
  }
  for (int u = 1; u <= n; u++)
    std::sort(G[u].begin(), G[u].end());

  s = 1;
  int stcnt = 0, edcnt = 0, alleq = 1;
  for (int u = 1; u <= n; u++) {
    if (ind[u] != outd[u]) {
      alleq = 0;
      if (ind[u] == outd[u] + 1)
        edcnt++;
      else if (outd[u] == ind[u] + 1)
        stcnt++, s = u;
      else
        fail();
    }
  }
  if (!alleq && (edcnt != 1 || stcnt != 1))
    fail();
  dfs(s);
  while (!st.empty()) {
    std::cout << st.top() << ' ';
    st.pop();
  }
  std::cout << '\n';
  return 0;
}
