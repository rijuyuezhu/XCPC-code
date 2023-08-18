#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
i64 n, m, b0, P, k;
i64 MOD(i64 v) {return v >= P ? v - P : v;}
struct mint {
  i64 v;
  mint(i64 v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator * (mint a, mint b) {return a.v * b.v % P;}
i64 s[MAXN], t[MAXN];
i64 nxt[MAXN];
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> b0 >> P;
  for (int i = 1; i <= n; i++)
    std::cin >> s[i];
  i64 cntq = 0;
  i64 z = 0;
  mint b = b0 % P, bp = 1, ans = 0;
  for (int i = 1; i <= m; i++) {
    int opt;
    std::cin >> opt;
    if (opt == 1) {
      i64 x, c;
      std::cin >> x >> c;
      x = (x ^ z) % n + 1;
      c = (c ^ z);
      s[x] = c;
    } else {
      std::cin >> k;
      for (int j = 1; j <= k; j++) {
        std::cin >> t[j];
        t[j] ^= z;
      }
      if (k < n)
        z = 0;
      else {
        nxt[1] = 0;
        for (int i = 2, j = 0; i <= n; i++) {
          while (j && s[j+1] != s[i])
            j = nxt[j];
          if (s[j+1] == s[i])
            j++;
          nxt[i] = j;
        }
        i64 cnt = 0;
        for (int i = 1, j = 0; i <= k; i++) {
          while (j && s[j+1] != t[i])
            j = nxt[j];
          if (s[j+1] == t[i])
            j++;
          if (j == n) {
            cnt++;
            j = nxt[j];
          }
        }
        z = nxt[n] * cnt;
      }
      ++cntq;
      bp = bp * b;
      ans = ans + (z % P) * bp;
    }
  }
  std::cout << ans.v << '\n';
  return 0;
}
