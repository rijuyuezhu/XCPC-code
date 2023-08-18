#include <iostream>
#include <algorithm>
using namespace std;
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
constexpr i64 LINF = 1e18;
int n, k, a[MAXN], vis[MAXN], b[MAXN], m;
void suc() {
  cout << "YES" << '\n';
  throw 0;
}
void fai() {
  cout << "NO" << '\n';
  throw 0;
}
void check() {
  if (m & 1) {
    i64 x = 0;
    for (int i = 2; i <= m; i++) {
      if (i & 1)
        x -= b[i];
      else 
        x += b[i];
    }
    x += b[1];
    if (x < 0 || x & 1)
      fai();
    x /= 2;
    for (int i = 2; i <= m; i++) {
      x = b[i] - x;
      if (x < 0)
        fai();
    }
  } else {
    i64 lo = 0, up = LINF, t = 0;
    for (int i = 2; i <= m; i++) {
      t = b[i] - t;
      if (i & 1)
        lo = max(lo, -t);
      else
        up = min(up, t);
    }
    if (lo > up)
      fai();
    if (t != b[1])
      fai();
  }
}
void dfs(int x) {
  vis[x] = 1;
  b[++m] = a[x];
  int nxt = x + k;
  if (nxt > n) 
    nxt -= n;
  if (vis[nxt]) {
    check();
    return ;
  }
  dfs(nxt);
}
void work() {
  cin >> n >> k;
  int allzero = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] > 0)
      allzero = 0;
    vis[i] = 0;
  }
  if (allzero)
    suc();
  if (k > n / 2)
    fai();
  for (int i = 1; i <= n; i++)
    if (!vis[i]) {
      m = 0;
      dfs(i);
    }
  suc();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    try {
      work();
    } catch(int) {
      
    }
  }
  return 0;
}
