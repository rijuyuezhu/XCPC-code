#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
int n, p[MAXN];
void ge(int n) {
  std::cout << n << ' '
            << n-3 << ' '
            << n-6 << ' ' 
            << n-1 << ' '
            << n-4 << ' '
            << n-7 << ' '
            << n-2 << ' '
            << n-5 << ' ';
}
void las(int n) {
  if (n == 1)
    std::cout << "1 ";
  else if (n == 2)
    std::cout << "2 1 ";
  else if (n == 3)
    std::cout << "3 2 1 ";
  else if (n == 4)
    std::cout << "4 3 2 1 "; 
  else if (n == 5)
    std::cout << "5 2 1 4 3 ";
  else if (n == 6)
    std::cout << "6 5 2 1 4 3";
  else if (n == 7)
    std::cout << "7 6 5 2 1 4 3";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    std::cin >> n;
    for (; n >= 8; n -= 8)
      ge(n);
    las(n);
    std::cout << '\n';
  }

  return 0;
}
