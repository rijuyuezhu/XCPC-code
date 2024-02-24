#include <iostream>
#include <algorithm>
#include <vector>

using i64 = long long;

constexpr int MAXN = 2e5 + 5;
int n;
int c[MAXN];

struct Edge {
  int v, nxt;
}e[MAXN];
int head[MAXN], cnt;

void addedge(int u, int v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}

int fa[MAXN], siz[MAXN], son[MAXN];

void dfs1(int u, int F) {
  fa[u] = F;
  siz[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u])
      continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]])
      son[u] = v;
  }
}
int cntcol[MAXN];
i64 sum[MAXN];
int maxcnt;

void add(int u) {
  int col = c[u];
  int &nowcnt = cntcol[col];
  sum[nowcnt] -= col;
  sum[++nowcnt] += col;
  if (sum[maxcnt+1] > 0)
    ++maxcnt;
}
void del(int u) {
  int col = c[u];
  int &nowcnt = cntcol[col];
  sum[nowcnt] -= col;
  sum[--nowcnt] += col;
  if (sum[maxcnt] == 0)
    --maxcnt;
}
void insert(int u) {
  add(u);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u])
      continue;
    insert(v);
  }
}

void erase(int u) {
  del(u);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u])
      continue;
    erase(v);
  }
}
i64 ans[MAXN];
void dfs2(int u) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u] || v == son[u])
      continue;
    dfs2(v);
  }
  if (son[u])
    dfs2(son[u]);
  add(u);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u] || v == son[u])
      continue;
    insert(v);
  }
  ans[u] = sum[maxcnt];
  if (fa[u] && son[fa[u]] != u)
    erase(u);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) 
    std::cin >> c[i];
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    addedge(u, v);
    addedge(v, u);
  }
  dfs1(1, 0);
  dfs2(1);
  for (int i = 1; i <= n; i++)
    std::cout << ans[i] << ' ';
  std::cout << '\n';
  return 0;
}
