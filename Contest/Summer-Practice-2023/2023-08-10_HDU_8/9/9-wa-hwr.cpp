#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 2005;
constexpr int INF = 0x3f3f3f3f;
int n, m;
int a[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN], pos[MAXN * MAXN][2];
int R[MAXN][MAXN], C[MAXN][MAXN], H[MAXN][MAXN];
void fbegin(int sx, int sy) {
  int x = sx, y = sy;
  for (; x <= n && y <= m; x++, y++)
    if (a[x][y] == a[x-1][y-1])
      f[x][y] = f[x-1][y-1] + 1;
    else 
      f[x][y] = 1;
}
// pos: 0 for x, 1 for time(sx+sy)
void gbegin(int sx, int sy) {
  int x = sx, y = sy;
  for(; x <= n && y >= 1; x++, y--) {
    int tim = pos[a[x][y]][1], px = pos[a[x][y]][0];
    if (tim == sx + sy)
      g[x][y] = x - px;
    else 
      g[x][y] = x;
    pos[a[x][y]][1] = x + y;
    pos[a[x][y]][0] = x;
  }
}
void work() {
  std::cin >> n >> m;

  //clear
  for (int i = 0; i <= n+1; i++)
    for (int j = 0; j <= m+1; j++)
      a[i][j] = f[i][j] = g[i][j] = R[i][j] = C[i][j] = H[i][j] = 0;
  for (int i = 0; i <= n * m + 1; i++)
    pos[i][0] = pos[i][1] = 0;

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      std::cin >> a[i][j];
  for (int i = 1; i <= n; i++)
    fbegin(i, 1);
  for (int j = 2; j <= m; j++)
    fbegin(1, j);
  for (int j = 1; j <= m; j++)
    gbegin(1, j);
  for (int i = 2; i <= n; i++)
    gbegin(i, m);
  for (int i = 0; i <= n+1; i++)
    R[i][0] = R[i][m+1] = C[i][0] = C[i][m+1] = H[i][0] = H[i][m+1] = INF;
  for (int j = 1; j <= m; j++)
    R[0][j] = R[n+1][j] = C[0][j] = C[n+1][j] = H[0][j] = H[n+1][j] = INF;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      R[i][j] = std::min(R[i-1][j] + 1, f[i][j]);
      C[i][j] = std::min(C[i][j-1] + 1, f[i][j]);
      H[i][j] = std::min(H[i-1][j+1] + 1, g[i][j]);
    }
  i64 ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      int ll = 1, rr = std::min(i, j), ret = -1;
      while (ll <= rr) {
        int t = (ll + rr) >> 1;
        if (R[i][j] >= t && C[i][j] >= t && H[i][j-t+1] >= t) {
          ret = t;
          ll = t + 1;
        } else 
          rr = t - 1;
      }
      ans += ret;
    }
  std::cout << ans << '\n';
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
