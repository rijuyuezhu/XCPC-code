#include <iostream>
#include <algorithm>
using i64 = long long;
using u64 = unsigned long long;

void work() {
  u64 a, b, r, xab;
  std::cin >> a >> b >> r;
  xab = a ^ b;
  if (xab == 0) {
    std::cout << 0 << '\n';
    return ;
  }
  int startbit = -1;
  u64 x = 0;
  i64 ans = 0;
  for (int i = 63; i >= 0; i--)
    if ((xab >> i) & 1) {
      startbit = i;
      break;
    }
  for (int i = startbit-1; i >= 0; i--)
    if ((xab >> i) & 1)
      if (((a >> i) & 1) == ((a >> startbit) & 1))
        if ((x | (1ull << i)) <= r)
          x |= 1ull << i;
  ans = std::abs(i64(a ^ x) - i64(b ^ x));
  x = 0;
  if ((1ull << startbit) <= r) {
    x = 1ull << startbit;
    for (int i = startbit-1; i >= 0; i--)
      if ((xab >> i) & 1)
        if (((a >> i) & 1) != ((a >> startbit) & 1))
          if ((x | (1ull << i)) <= r)
            x |= 1ull << i;
    ans = std::min(ans, std::abs(i64(a ^ x) - i64(b ^ x)));
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
