#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;
i64 X;
int a[70], n;
void work() {
  std::cin >> X;

  n = 0;
  i64 tmp = X;
  while (tmp) {
    a[n++] = tmp & 1;
    tmp >>= 1;
  }
  std::vector<int> ans;
  for (int i = 0; i < n-1; i++)
    ans.push_back(i);
  for (int i = n-2; i >= 0; i--)
    if (a[i])
      ans.push_back(i);
  std::cout << (int)ans.size() << '\n';
  for (auto v : ans)
    std::cout << v << ' ';
  std::cout << '\n';
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
