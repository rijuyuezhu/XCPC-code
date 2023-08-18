#include <cmath>
#include <iostream>
#include <algorithm>
using i64 = long long;

void work() {
  i64 a, b, d;
  std::cin >> a >> b;
  d = std::abs(a-b);

  //test1
  i64 sd = (i64)round(sqrt(d));
  if (sd * sd == d) {
    std::cout << 1 << '\n';
    return ;
  }
  //test 2
  if (d % 2 == 1 || d % 4 == 0) {
    std::cout << 2 << '\n';
    return ;
  }
  for (i64 i = 1; i * i < d; i += 2) {
    i64 sj = d - i * i;
    i64 j = (i64)round(sqrt(sj));
    if (j * j == sj) {
      std::cout << 2 << '\n';
      return ;
    }
  } 
  std::cout << 3 << '\n';
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
