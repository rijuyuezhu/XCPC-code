#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using i64 = long long;
constexpr int MAXN = 105;

int n;
std::string s;
std::vector<int> seq;

void work() {
  std::cin >> n;
  std::cin >> s;
  if (n & 1) {
    std::cout << -1 << '\n';
    return ;
  }
  s = ' ' + s;
  s.push_back(0);
  int L = 1, R = n;
  while (L <= R) {
    
  }
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
