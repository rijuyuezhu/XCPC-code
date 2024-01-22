#include <iostream>
#include <algorithm>
#include <string>
using i64 = long long;

int n;
std::string s;
void work() {
  std::cin >> n;
  std::cin >> s;
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += s[i] == '+' ? 1 : -1;
  ans = std::abs(ans);
  std::cout << ans << '\n';
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
