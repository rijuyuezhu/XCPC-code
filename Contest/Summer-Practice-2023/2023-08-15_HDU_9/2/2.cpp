#include <iostream>
#include <algorithm>
#include <map>
using i64 = long long;
constexpr int INF = 0x3f3f3f3f;
std::map<i64, int> mp;
int dfs(i64 n, int cnt) {
  if (n == 1)
    return 0;
  auto it = mp.find((cnt - 1) * n);
  if (it != mp.end())
    return it->second;
  int ret = INF;
  if (cnt > 0)
    ret = std::min(ret, dfs(n-1, cnt-1));
  if (n % 2 == 0)
    ret = std::min(ret, dfs(n / 2, 2));
  if (n % 3 == 0)
    ret = std::min(ret, dfs(n / 3, 2));
  mp[n] = ret + 1;
  return ret + 1;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    mp.clear();
    i64 n;
    std::cin >> n;
    std::cout << dfs(n, 2) << '\n';
  }
  return 0;
}
