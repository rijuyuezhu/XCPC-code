#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;
int n;
void work() {
  std::cin >> n;
  auto cnt = std::vector(n+1, std::vector<char>());
  for (char c = 'z'; c >= 'a'; c--)
    cnt[0].push_back(c);
  for (int i = 1; i <= n; i++) {
    int a;
    std::cin >> a;
    char v = cnt[a].back(); cnt[a].pop_back();
    cnt[a+1].push_back(v);
    std::cout << v;
  }
  std::cout << '\n';
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
