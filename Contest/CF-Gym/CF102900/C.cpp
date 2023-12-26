#include <iostream>
#include <algorithm>
#include <cstring>
using i64 = long long;
constexpr i64 P = 1e9 + 7;
i64 X, Y;
i64 tab[35][2][2];

static inline int nxtCon(int t, int V, int now, int con) {
  if (!con)
    return 0;
  return now == ((V >> t) & 1);
}

i64 dfs(int t, int conX, int conY) {
  if (t < 0)
    return 1;
  if (tab[t][conX][conY] != -1)
    return tab[t][conX][conY];
  i64 ans = 0;
  int canXbe1 = !conX || ((X >> t) & 1);
  int canYbe1 = !conY || ((Y >> t) & 1);
  // case1: 0 & 0
  ans += dfs(t-1, nxtCon(t, X, 0, conX), nxtCon(t, Y, 0, conY));
  if (canXbe1) // 1 & 0
    ans += dfs(t-1, nxtCon(t, X, 1, conX), nxtCon(t, Y, 0, conY));
  if (canYbe1)
    ans += dfs(t-1, nxtCon(t, X, 0, conX), nxtCon(t, Y, 1, conY));
  return tab[t][conX][conY] = ans % P;
}

i64 calc(int t) {
  i64 ans = 0;
  int conX = (X >> t) == 0;
  int conY = (Y >> t) == 0;
  int canXbe1 = !conX || ((X >> (t-1)) & 1);
  int canYbe1 = !conY || ((Y >> (t-1)) & 1);
  if (canXbe1) {
    ans += dfs(t-2, nxtCon(t-1, X, 1, conX), nxtCon(t-1, Y, 0, conY));
  }
  if (canYbe1) {
    ans += dfs(t-2, nxtCon(t-1, X, 0, conX), nxtCon(t-1, Y, 1, conY));
  }
  return ans % P;
}

void work() {
  memset(tab, 0xff, sizeof(tab));
  std::cin >> X >> Y;
  i64 ans = 0;
  for (int t = 31; t >= 1; t--) { // log = t
    // [MAX, t] for i j is all zero
    // exactly one of i and j in bit t-1 is 1.
    // alter in [t-2, 0] or both 0
    ans = (ans + t * calc(t)) % P;
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
