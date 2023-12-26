#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
constexpr int P = 19930726;
int n;
i64 K;
char s[MAXN];
int r[MAXN];
i64 sum[MAXN];

i64 qpow(i64 a, i64 n) {
  i64 ret = 1;
  for (; n; n >>= 1, a = (a * a) % P)
    if (n & 1)
      ret = (ret * a) % P;
  return ret;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> K;
  std::cin >> (s + 2);
  s[1] = -1;
  int c = 0;
  for (int i = 1; i <= n+1; i++) {
    if (i < c + r[c])
      r[i] = std::min(c + r[c] - i, r[2 * c - i]);
    while (i + r[i] <= n+1 && s[i + r[i]] == s[i - r[i]])
      r[i]++;
    if (i + r[i] > c + r[c])
      c = i;
  }
  for (int i = 2; i <= n+1; i++) {
    sum[1]++; // 2 * i - 1
    sum[r[i]+1]--;
  }
  i64 tot = 0;
  for (int i = 1; i <= n; i++) {
    sum[i] += sum[i-1];
    tot += sum[i];
  }
  if (tot < K) {
    std::cout << -1 << '\n';
    return 0;
  }
  i64 ans = 1;
  for (int i = n; i >= 1; i--) {
    i64 val = std::min(K, sum[i]);
    K -= val;
    ans = (ans * qpow(2 * i - 1, val)) % P;
    // if(val > 0)
      // fprintf(stderr, "len: %d; count: %lld\n", 2 * i - 1, val);
  }
  std::cout << ans << '\n';
  return 0;
}
