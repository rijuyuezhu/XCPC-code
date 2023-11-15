#include <iostream>
#include <algorithm>
using i64 = long long;
int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y);}

void work(int te) {
  int r, b;
  std::cin >> r >> b;
  int x, y;
  x = r * (r - 1) / 2;
  y = (r + b) * (r + b - 1) / 2;
  int g = gcd(x, y);
  x /= g;
  y /= g;
  std::cout << "Case #" << te << ": " << x << "/" << y << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  for (int i = 1; i <= T; i++)
    work(i);
  return 0;
}
