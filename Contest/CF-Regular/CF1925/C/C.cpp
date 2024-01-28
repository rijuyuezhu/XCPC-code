#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using i64 = long long;
constexpr int MAXN = 30;
constexpr int MAXK = 30;
constexpr int MAXL = 1000;
int n, k, m;
std::string s;
std::vector<int> num[MAXK], ans;
int getnxt(int c, int now) {
  auto it = std::upper_bound(num[c].begin(), num[c].end(), now);
  if (it == num[c].end())
    return -1;
  return *it;
}
void work() {
  std::cin >> n >> k >> m;
  std::cin >> s;
  for (int i = 0; i < k; i++)
    num[i].clear();
  ans.clear();
  for (int i = 0; i < m; i++)
    num[s[i] - 'a'].push_back(i);
  int now = -1, fail = 0;
  for (int t = 1; t <= n; t++) {
    int last = -1, lastnum = -1;
    for (int i = 0; i < k; i++) {
      int lasti = getnxt(i, now);
      if (lasti == -1) {
        ans.push_back(i);
        fail = 1;
        goto END;
      }
      if (last == -1 || lastnum < lasti)
        last = i, lastnum = lasti;
    }
    ans.push_back(last);
    now = lastnum;
  }
END:
  if (fail) {
    for (int i = ans.size(); i < n; i++)
      ans.push_back(0);
    std::cout << "NO" << '\n';
    for (auto v : ans)
      std::cout << char(v + 'a');
    std::cout << '\n';
  } else {
    std::cout << "YES" << '\n';
  }
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
