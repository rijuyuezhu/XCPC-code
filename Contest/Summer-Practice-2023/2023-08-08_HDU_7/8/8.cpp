#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int X, Y, n;
struct Edge {
  int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt, tag[MAXN], a[MAXN], _a, mxdis[MAXN], f[MAXN], g[MAXN];
void addedge(int u, int v) {
  e[++cnt] = {v, head[u]}; head[u] = cnt;
}
void clear() {
  cnt = _a = 0;
  for (int i = 1; i <= n; i++) {
    head[i] = 0;
    tag[i] = 0;
    mxdis[i] = 0;
    f[i] = g[i] = 0;
  }
}
bool dfs1(int u, int fa) {
  if (u == Y) {
    tag[u] = 1;
    a[_a++] = u;
    return 1;
  }
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    if (dfs1(v, u)) {
      tag[u] = 1;
      a[_a++] = u;
      return 1;
    }
  }
  return 0;
}
void dfs2(int u, int fa) {
  mxdis[u] = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || tag[v])
      continue;
    dfs2(v, u);
    mxdis[u] = std::max(mxdis[u], mxdis[v] + 1);
  }
}
int A(int pos) {
  return mxdis[a[pos]];
}
int V1(int pos) {
  return A(pos) - pos;
}
int V2(int pos) {
  return A(pos) + pos;
}
void Dp() {
  int n = _a;
  if (n & 1) {
    f[(n-1)/2] = (A((n-1)/2) > A((n+1)/2));
    int v1 = V1((n+1)/2);
    int v2 = -INF;
    for (int i = (n-3) / 2; i >= 0; i--) {
      v2 = std::max(v2, std::max(V2(i+1), V2(n-i-1)));
      g[i] = !f[i+1] || (A(n-i) > -i-1 + v2);
      v1 = std::max(v1, std::max(V1(i+1), V1(n-i)));
      f[i] = !g[i] || (A(i) > n-i + v1);
    }
  } else {
    g[n/2-1] = (A(n/2+1)>A(n/2));
    int v1 = -INF;
    int v2 = -INF;
    for (int i = n/2-1; i >= 0; i--) {
      v2 = std::max(v2, std::max(V2(i+1), V2(n-i-1)));
      if (i != n/2-1)
        g[i] = !f[i+1] || (A(n-i) > -i-1 + v2);
      v1 = std::max(v1, std::max(V1(i+1), V1(n-i)));
      f[i] = !g[i] || (A(i) > n-i + v1);
    }
  }
}
void work() {
  std::cin >> n >> X >> Y;
  clear();
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    addedge(u, v);
    addedge(v, u);
  }
  dfs1(X, 0);
  --_a;
  std::reverse(a, a + 1 + _a);
  for (int i = 0; i <= _a; i++)
    dfs2(a[i], 0);
  Dp();
  std::cout << f[0] << '\n';
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
