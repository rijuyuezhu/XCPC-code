#include <iostream>
#include <algorithm>
using i64 = long long;

void work() {
  int a, b;
  std::cin >> a >> b;
  std::cout << ((a + b) % 2 == 0 ? "Bob\n" : "Alice\n");
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
