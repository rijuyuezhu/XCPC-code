#include <iostream>
#include <vector>
#include <algorithm>
using i64 = long long;

i64 n;
std::vector<i64> a, s, leq;

i64 getres(int l, int r) {
  if (leq[r] <= l) // all equal
    return a[l];
  else
    return s[r] - s[l-1];
}

void work() {
  std::cin >> n;
  a.assign(n+1, 0);
  s.assign(n+1, 0);
  leq.assign(n+1, 0);
  for (i64 i = 1; i <= n; ++i) {
    std::cin >> a[i];
    s[i] = s[i-1] + a[i];
  }
  leq[1] = 1;
  for (i64 i = 2; i <= n; ++i)
    if (a[i] == a[i-1])
      leq[i] = leq[i-1];
    else
      leq[i] = i;
  for (i64 i = 1; i <= n; ++i) {
    i64 L = 1, R = i-1, ansl = n+1;
    while (L <= R) {
      i64 M = (L + R) >> 1;
      if (getres(i - M, i-1) > a[i]) {
        ansl = M;
        R = M - 1;
      } else {
        L = M + 1;
      }
    }
    L = 1, R = n - i;
    i64 ansr = n+1;
    while (L <= R) {
      i64 M = (L + R) >> 1;
      if (getres(i+1, i+M) > a[i]) {
        ansr = M;
        R = M - 1;
      } else {
        L = M + 1;
      }
    }
    i64 ans = std::min(ansl, ansr);
    if (ans == n+1)
      std::cout << -1 << ' ';
    else
      std::cout << ans << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  i64 T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
