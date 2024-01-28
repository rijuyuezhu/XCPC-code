#include <iostream>
#include <algorithm>
#include <map>
using i64 = long long;
constexpr int MAXN = 3e5 + 5;
int n, m, q;
std::map<int, i64> har;
i64 X[MAXN], V[MAXN];
struct BIT {
  i64 t[MAXN];
  void add(int x, i64 v) {
    for (int i = x; i <= n; i += i & -i)
      t[i] += v;
  }
  i64 sum(int x) {
    i64 ans = 0;
    for (int i = x; i; i -= i & -i)
      ans += t[i];
    return ans;
  }
  i64 sum(int x, int y) {
    return sum(y) - sum(x-1);
  }
  void mdy(int x, i64 v) {
    i64 ori = sum(x, x);
    add(x, v-ori);
  }
}T;
i64 calc(i64 LeftV, int rightpos, int l, int r) {
  i64 len = r - l + 1;
  i64 beg = rightpos - r;
  i64 end = rightpos - l;
  return LeftV * (((beg + end) * len) / 2);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> q;
  for (int i = 1; i <= m; i++)
    std::cin >> X[i];
  for (int i = 1; i <= m; i++)
    std::cin >> V[i];
  for (int i = 1; i <= m; i++)
    har[X[i]] = V[i];
  for (auto now = har.begin(); now != har.end(); now++) {
    // T.add(X[i], calc(V[i], X[i+1], X[i] + 1, X[i+1]));
    auto nxt = now; ++nxt;
    if (nxt == har.end())
      continue;
    T.add(now->first, calc(now->second, nxt->first, now->first+1, nxt->first));
  }
  while (q--) {
    int opt;
    std::cin >> opt;
    if (opt == 1) {
      i64 x, v;
      std::cin >> x >> v;
      har[x] = v;
      auto now = har.find(x);
      auto pre = now; --pre;
      auto nxt = now; ++nxt;
      T.mdy(pre->first, calc(pre->second, x, pre->first + 1, x));
      T.add(x, calc(v, nxt->first, x + 1, nxt->first));
    } else {
      int L, R;
      std::cin >> L >> R;
      auto beg = har.lower_bound(L);
      auto end = --har.upper_bound(R);
      int isemp = (beg->first > R);
      i64 ans = 0;
      if (!isemp) {
        ans += T.sum(beg->first, end->first-1); // middle
        if (beg != har.begin()) { // pre
          auto prebeg = beg; --prebeg;
          ans += calc(prebeg->second, beg->first, L, beg->first);
        }
        if (end != --har.end()) { // suf
          auto sufend = end; ++sufend;
          ans += calc(end->second, sufend->first, end->first + 1, R);
        }
      } else {
        auto nxt = har.upper_bound(R);
        auto pre = nxt; --pre;
        ans = calc(pre->second, nxt->first, L, R);
      }
      std::cout << ans << '\n';
    }
  }
  return 0;
}
