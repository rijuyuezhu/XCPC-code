#include <iostream>
#include <queue>
#include <algorithm>
using i64 = long long;
using pii = std::pair<int, int>;

constexpr int MAXN = 4e5 + 5;
constexpr int INF = 0x3f3f3f3f;
constexpr int MAXM = 4e5 + 5;

int n, m, A, B, l[MAXN];
struct Edge {
  int v, nxt;
}e[MAXM];
int head[MAXN], cnt;

void addedge(int u, int v) {
  e[++cnt] = {v, head[u]}; head[u] = cnt;
}
int dist[MAXN], vis[MAXN];
int cntv[MAXN];
void dijkstra(int s) {
  std::priority_queue<pii> pq;
  for (int i = 1; i <= n; i++)
    dist[i] = INF, vis[i] = 0;
  dist[s] = 0;
  pq.push(pii(0, s));
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop();
    if (vis[u])
      continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      int expect_time = dist[u] + 1;
      if (A > B) {
        expect_time = std::max(expect_time, (l[v] - l[1] + 2 * A - B) / (A - B));
      }
      int most_time = INF;
      if (A < B) {
        most_time = std::min(most_time, (l[1] - l[v] - A - 1) / (B - A));
      } else if (A == B) {
        if (l[1] - l[v] - A <= 0)
          most_time = 0;
      }
      if (expect_time <= most_time && dist[v] > expect_time) {
        dist[v] = expect_time;
        pq.push(pii(-dist[v], v));
      }
    }
  }
}

void work() {
  std::cin >> n >> m >> A >> B;
  for (int i = 1; i <= n; i++)
    head[i] = 0;
  cnt = 0;
  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    addedge(u, v);
    addedge(v, u);
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> l[i];
  }
  dijkstra(1);
  int win = 1;
  if (!vis[n] || dist[n] > n)
    win = 0;
  else {
    for (int i = 0; i <= n; i++)
      cntv[i] = 0;
    for (int i = 2; i <= n; i++)
      if (dist[i] >= 1 && dist[i] <= n)
        cntv[dist[i]]++;
    for (int i = 1; i <= dist[n]; i++) {
      cntv[i] += cntv[i-1];
      if (cntv[i] < i) {
        win = 0;
        break;
      }
    }
  }
  if (win) {
    std::cout << dist[n] << '\n';
  } else {
    std::cout << -1 << '\n';
  }
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
