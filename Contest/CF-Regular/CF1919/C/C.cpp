#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 2e5 + 5;
int n, a[MAXN], f[MAXN];
struct BIT {
  int t[MAXN];
  void clear() {
    for (int i = 1; i <= n; i++)
      t[i] = 0;
  }
  int lowbit(int x) {return x & -x;}
  void ins(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
      t[i] = std::max(t[i], v);
  }
  int premax(int x) {
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
      ans = std::max(ans, t[i]);
    return ans;
  }
}T;
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  T.clear();
  f[0] = 0;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = T.premax(a[i]-1) + 1;
    T.ins(a[i], f[i]);
    ans = std::max(ans, f[i]);
  }
  std::cout << std::max(0, ans - 2) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--)
    work();
  return 0;
}
