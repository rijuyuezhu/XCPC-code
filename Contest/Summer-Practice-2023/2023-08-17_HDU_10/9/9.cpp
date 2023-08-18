#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
constexpr int MAXC = 5e5 + 5;
int n, c;
std::vector<int> pos[MAXC];
void clear() {
  for (int i = 1; i <= c; i++)
    pos[i].clear();
}
void work() {
  std::cin >> n >> c;
  clear();
  
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
