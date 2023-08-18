#include <iostream>
#include <algorithm>
#include <vector>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, a[MAXN], L = INF, R = -INF, cnt[MAXN];
std::vector<int> pos[MAXN];
i64 ans;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    std::vector<int> &now = pos[a[i]], &pre = pos[a[i]-1];
    cnt[a[i]]++; now.push_back(i);
    if (a[i] != 1) {
      int l, r = i;
      if ((int)pre.size() < cnt[a[i]])
        l = 0;
      else 
        l = pre[(int)pre.size() - cnt[a[i]]] + 1;
      L = std::min(L, l);
      R = std::max(R, r);
    }
    if (L <= R)
      ans += L-1 + i-R;
    else 
      ans += i;
  }
  std::cout << ans << '\n';
  return 0;
}
