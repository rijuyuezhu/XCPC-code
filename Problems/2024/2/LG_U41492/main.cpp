#include <iostream>
#include <algorithm>
#include <vector>

using i64 = long long;
constexpr i64 MAXN = 2e5 + 5;

i64 n, m;
struct Edge {
  i64 v, nxt;
}e[MAXN];
i64 head[MAXN], cnt;
void addedge(i64 u, i64 v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}

i64 c[MAXN];

i64 fa[MAXN], siz[MAXN], son[MAXN], dfn[MAXN], tim, nde[MAXN];

void dfs1(i64 u, i64 F) {
  dfn[u] = ++tim;
  nde[tim] = u;
  fa[u] = F;
  siz[u] = 1;
  for (i64 i = head[u]; i; i = e[i].nxt) {
    i64 v = e[i].v;
    if (v == F)
      continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[son[u]] < siz[v])
      son[u] = v;
  }
}

i64 ans[MAXN], cntcol[MAXN], totcol;

void addcol(i64 c) {
  if (cntcol[c] == 0)
    ++totcol;
  ++cntcol[c];
}

void delcol(i64 c) {
  --cntcol[c];
  if (cntcol[c] == 0)
    --totcol;
}

void dfs2(i64 u, bool keep) {
  for (i64 i = head[u]; i; i = e[i].nxt) {
    i64 v = e[i].v;
    if (v == fa[u] || v == son[u])
      continue;
    dfs2(v, false);
  }
  if (son[u])
    dfs2(son[u], true);
  for (i64 i = head[u]; i; i = e[i].nxt) {
    i64 v = e[i].v;
    if (v == fa[u] || v == son[u])
      continue;
    for (i64 j = dfn[v]; j < dfn[v] + siz[v]; j++)
      addcol(c[nde[j]]);
  }
  addcol(c[u]);
  ans[u] = totcol;
  if (!keep) {
    for (i64 j = dfn[u]; j < dfn[u] + siz[u]; j++)
      delcol(c[nde[j]]);
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (i64 i = 1; i < n; ++i) {
    i64 u, v;
    std::cin >> u >> v;
    addedge(u, v);
    addedge(v, u);
  }
  for (i64 i = 1; i <= n; ++i)
    std::cin >> c[i];
  dfs1(1, 0);
  dfs2(1, false);

  std::cin >> m;
  for (i64 i = 1; i <= m; ++i) {
    i64 u;
    std::cin >> u;
    std::cout << ans[u] << '\n';
  }
  return 0;
}
