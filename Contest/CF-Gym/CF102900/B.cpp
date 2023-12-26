#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e3 + 5;
int n, m;
char A[MAXN][MAXN], B[MAXN][MAXN];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++)
    std::cin >> (A[i] + 1);
  for (int i = 1; i <= n; i++)
    std::cin >> (B[i] + 1);
  int cnt = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (A[i][j] != B[i][j])
        cnt++;
  if (cnt <= n * m / 2) {
    for (int i = 1; i <= n; i++)
      std::cout << (A[i] + 1) << '\n';
  } else {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
        if (A[i][j] == 'X')
          std::cout << '.';
        else
          std::cout << 'X';
      std::cout << '\n';
    }
  }

  return 0;
}
