#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 2e5 + 5;
int n;
int a[MAXN], nxt[MAXN];

void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  nxt[n] = n+1;
  for (int i = n-1; i >= 1; i--)
    nxt[i] = (a[i] == a[i+1]) ? nxt[i+1] : i+1;
  int q;
  std::cin >> q;
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    int X = l, Y = nxt[l];
    if (Y > r) {
      std::cout << "-1 -1\n";
    } else {
      std::cout << X << ' ' << Y << '\n';
    }
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
