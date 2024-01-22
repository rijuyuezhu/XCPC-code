#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
int n, c[MAXN], cnt[MAXN];
char buff[MAXN];
void work() {
  std::cin >> n;
  std::cin >> (buff + 1);
  for (int i = 1; i <= n; i++)
    cnt[i] = 0;
  for (int i = 1; i <= n; i++) {
    c[i] = buff[i] - '0';
    int nxt = i + (i & -i);
    if (nxt <= n) 
      cnt[nxt] += c[i];
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (c[i]) {
      if (cnt[i] == 0)
        ans++;
    } else { //c[i] == 0
      if (cnt[i] == 1)
        ans++;
    }
  }
  std::cout << ans << '\n';
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
