#include <iostream>
#include <algorithm>
#include <iterator>
using i64 = long long;

constexpr int MAXN = 2e5 + 5;
int n, k, ans[MAXN];
void work() {
  std::cin >> n >> k;
  int L = 1, R = n;
  for (int i = 1; i <= k; i++) {
    if (i % 2 == 1) {
      for (int j = i; j <= n; j += k)
        ans[j] = R--;
    } else {
      for (int j = i; j <= n; j += k)
        ans[j] = L++;
    }
  }
  std::copy(ans + 1, ans + 1 + n, std::ostream_iterator<int>(std::cout, " "));
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
