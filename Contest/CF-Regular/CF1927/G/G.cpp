#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using i64 = long long;

constexpr int MAXN = 105;
int n, f[MAXN], g[MAXN], a[MAXN];
std::vector<int> Rig[MAXN];
int left(int i) {
  return std::max(i - a[i] + 1, 1);
}
int right(int i) {
  return std::min(i + a[i] - 1, n);
}
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  f[0] = 0; g[0] = 0;
  for (int i = 1; i <= n; i++)
    Rig[i].clear();
  for (int i = 1; i <= n; i++) {
    Rig[right(i)].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    f[i] = g[i] = n+1;
    for (int j = left(i)-1; j < i; j++) {
      f[i] = std::min(f[i], std::min(f[j], g[j]) + 1);
    }
    for (auto k : Rig[i]) {
      for (int j = k-1; j < i; j++)
        if (j != k) {
          g[i] = std::min(g[i], std::min(f[j], g[j]) + 1);
        } else {
          g[i] = std::min(g[i], g[j] + 1);
        }
    }
  }
  std::cout << std::min(f[n], g[n]) << '\n';
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
