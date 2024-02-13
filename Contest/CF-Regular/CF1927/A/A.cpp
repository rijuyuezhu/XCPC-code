#include <iostream>
#include <algorithm>
#include <iterator>
using i64 = long long;

void work() {
  int n;
  std::string s;
  std::cin >> n >> s;
  int leftest = -1, rightest = -1;
  for (int i = 0; i < n; i++)
    if (s[i] == 'B') {
      if (leftest == -1)
        leftest = i;
      rightest = i;
    }
  if (leftest == -1)
    std::cout << 0 << '\n';
  else
    std::cout << (rightest - leftest + 1) << '\n';
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
