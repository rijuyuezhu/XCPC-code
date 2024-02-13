#include <iostream>
#include <algorithm>
#include <set>
using i64 = long long;

int n, m, k;
void work() {
  std::set<int> a, b;
  bool ok = true;
  int A = 0, B = 0;
  std::cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    int v;
    std::cin >> v;
    a.insert(v);
  }
  for (int i = 1; i <= m; i++) {
    int v;
    std::cin >> v;
    b.insert(v);
  }
  for (int i = 1; i <= k; i++) {
    bool fa = a.find(i) != a.end();
    bool fb = b.find(i) != b.end();
    if (!fa && !fb) {
      ok = false;
      break;
    } else if (!fa) {
      B++;
    } else if (!fb) {
      A++;
    }
  }
  if (A > k/2 || B > k/2)
    ok = false;
  std::cout << (ok ? "YES" : "NO") << '\n';
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
