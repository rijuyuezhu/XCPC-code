#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 6e5 + 5;
int n, a[MAXN], d[MAXN], nxt[MAXN], pre[MAXN];
int chk_list[MAXN], _chk;
int die_list[MAXN], _die;
int died[MAXN];
int getnxt(int x) {
  return nxt[x] == x ? x : nxt[x] = getnxt(nxt[x]);
}
int getpre(int x) {
  return pre[x] == x ? x : pre[x] = getpre(pre[x]);
}
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  for (int i = 1; i <= n; i++)
    std::cin >> d[i];
  for (int i = 0; i <= n+1; i++)
    nxt[i] = i, pre[i] = i, died[i] = 0;
  _chk = 0; _die = 0;
  for (int i = 1; i <= n; i++)
    chk_list[++_chk] = i;
  for (int round = 1; round <= n; round++) {
    _die = 0;
    int ans = 0;
    for (int i = 1; i <= _chk; i++) {
      int v = chk_list[i];
      if (died[v] || v <= 0 || v >= n+1)
        continue;
      int P = getpre(v-1);
      int N = getnxt(v+1);
      int total = (P == 0 ? 0 : a[P]) + (N == n+1 ? 0 : a[N]);
      if (total > d[v])
        died[v] = 1, die_list[++_die] = v;
    }
    ans += _die;
    _chk = 0;
    for (int i = 1; i <= _die; i++) {
      int v = die_list[i];
      nxt[getnxt(v)] = getnxt(v+1);
      pre[getpre(v)] = getpre(v-1);
    }
    for (int i = 1; i <= _die; i++) {
      int v = die_list[i];
      chk_list[++_chk] = getnxt(v+1);
      chk_list[++_chk] = getpre(v-1);
    }
    std::cout << ans << ' ';
  }
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
