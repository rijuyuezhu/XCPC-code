#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using i64 = long long;
int n;
std::map<std::string, int> mp;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    int c;
    std::cin >> c;
    for (int j = 1; j <= c; j++) {
      std::string s;
      std::cin >> s;
      mp[s]++;
    }
  }
  int cnt = 0;
  for (auto pr : mp)
    if (pr.second == n)
      cnt++;
  std::cout << cnt << '\n';
  for (auto pr : mp)
    if (pr.second == n)
      std::cout << pr.first << '\n';
  return 0;
}
