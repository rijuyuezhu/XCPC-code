#include <iostream>
#include <algorithm>
#include <string>
using i64 = long long;

int n;
std::string a, b, c;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    std::cin >> n;
    std::cin >> a >> b >> c;
    int flag = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == b[i] && a[i] != c[i])
        flag = 1;
      if (a[i] != b[i] && a[i] != c[i] && b[i] != c[i])
        flag = 1;
    }
    if (flag)
      std::cout << "YES" << '\n';
    else
      std::cout << "NO"  << '\n';
  }
  return 0;
}
