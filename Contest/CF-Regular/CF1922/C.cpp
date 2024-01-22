#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
int n;
i64 a[MAXN], L[MAXN], sL[MAXN], R[MAXN], sR[MAXN];
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  a[0] = 0;
  a[n+1] = a[n];
  sL[0] = sR[0] = 0;
  for (int i = 1; i <= n; i++) {
    if (i == 1 || (i < n && a[i] - a[i-1] > a[i+1] - a[i])) {
      L[i] = a[i] - a[i-1];
      R[i] = 1;
    } else {
      L[i] = 1;
      R[i] = a[i+1] - a[i];
    }
    sL[i] = sL[i-1] + L[i];
    sR[i] = sR[i-1] + R[i];
  }
  int m;
  std::cin >> m;
  while (m--) {
    int x, y;
    std::cin >> x >> y;
    if (x < y) {
      std::cout << (sR[y-1] - sR[x-1]) << '\n';
    } else {
      std::cout << (sL[x] - sL[y]) << '\n';
    }
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
