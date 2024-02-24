#include <iostream>
#include <algorithm>
using i64 = long long;

constexpr int MAXN = 55;
int n;
int a[MAXN];

auto work() -> void {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  int leftmost = -1, rightmost = -1, cnt = 0;
  for (int i = 1; i <= n; i++)
    if (a[i] == 1) {
      if (leftmost == -1)
        leftmost = i;
      rightmost = i;
      cnt++;
    }
  std::cout << (rightmost - leftmost + 1 - cnt) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--)
    work();
}
