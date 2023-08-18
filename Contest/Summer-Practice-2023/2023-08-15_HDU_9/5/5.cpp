#include <iostream>
#include <algorithm>
#include <string>
using i64 = long long;
constexpr int MAXN = 5e5 + 5;
std::string s;
int n, m, a[MAXN];
int read(int &i) {
  int ret = 0;
  for (; i < (int)s.length() && (s[i] < '0' || s[i] > '9'); i++);
  for (; i < (int)s.length() && s[i] >= '0' && s[i] <= '9'; i++)
    ret = ret * 10 + s[i] - '0';
  return ret;
}
void work() {
  std::getline(std::cin, s);
  std::getline(std::cin, s);
  std::cin >> n >> m;
  int id = 0;
  for (int i = 1; i <= n * m; i++)
    a[i] = read(id);
  std::cout << '[';
  for (int i = 1; i <= n; i++) {
    std::cout << '[';
    for (int j = m * (i-1) + 1; j <= m * i; j++)
      std::cout << a[j] << (j == m * i ? "]" : ", ");
    std::cout << (i == n ? "]" : ", ");
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
