#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 15;
constexpr int MAXT = 305;
constexpr int MAXK = 11;
constexpr int MAXU = (1 << 10) + 5;
constexpr int P = 1e9 + 7;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
  int v;
  mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint& operator += (mint &a, mint b) {return a = a + b;}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1LL * a.v * b.v % P;}
int n, T, k, m, U, cnt[MAXT];
mint f[MAXT][MAXN][MAXU];
int siz(int S) {
  int ret = 0;
  for (; S; ret++, S -= (S & -S));
  return ret;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> T >> k >> m;
  U = (1 << k) - 1;
  for (int i = 1; i <= n; i++) {
    int x;
    std::cin >> x;
    cnt[x]++;
  }
  f[0][0][0] = 1;
  for (int t = 1; t <= T; t++)
    for (int i = 0; i <= n; i++) {
      for (int S = 0; S <= U; S++) {
        if (siz(S) > m)
          continue;
        if (~S & 1) {
          if (i - cnt[t] >= 0) { 
            f[t][i][S] += f[t-1][i - cnt[t]][S >> 1] + f[t-1][i - cnt[t]][S >> 1 | (1 << (k-1))];
          }
        } else {
          if (i - cnt[t] + 1 >= 0) { //put one
              f[t][i][S] += 
                (i + 1) * 
                ( f[t-1][i - cnt[t] + 1][S >> 1] + 
                 f[t-1][i - cnt[t] + 1][S >> 1 | (1 << (k-1))] );
          }
        }
      }
    }
  mint ans = 0;
  for (int S = 0; S <= U; S++)
    ans += f[T][0][S];
  std::cout << ans.v << '\n';
  
  return 0;
}
