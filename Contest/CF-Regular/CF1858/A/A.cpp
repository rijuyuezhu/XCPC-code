#include <iostream>
#include <algorithm>
using i64 = long long;

void work() {
  i64 a, b, c;
  std::cin >> a >> b >> c;
  if (c & 1)
    a++;
  if (a > b)
    std::cout << "First\n";
  else
    std::cout << "Second\n";
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
