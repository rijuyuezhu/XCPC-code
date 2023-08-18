#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 19, MAXM = (1 << 18) + 5, B = 30;
int n, m, a[MAXM], b[MAXM];
int t[B], lbsiz;
bool ins(int x) {
  for (int i = B-1; i >= 0; i--) {
    if ((x >> i) & 1) {
      if (!t[i]) {
        t[i] = x;
        lbsiz++;
        return 1;
      } else {
        x ^= t[i];
      }
    }
  }
  return 0;
}
void work() {
  std::cin >> n;
  m = (1 << n);
  for (int i = 1; i < m; i++) {
    std::cin >> a[i];
    b[i] = 0;
  }
  std::sort(a + 1, a + m);
  int cnt = -1, ncnt = 1;
  a[0] = a[m] = -1;
  for (int i = 2; i <= m; i++) {
    if (a[i] == a[i-1])
      ncnt++;
    else {
      if (a[i-1] == 0)
        ++ncnt;
      if (cnt == ncnt || cnt == -1)
        cnt = ncnt;
      else {
        std::cout << -1 << '\n';
        throw 0;
      }
      ncnt = 1;
    }
  }
  int _a = std::unique(a + 1, a + m) - a - 1;
  for (int i = B-1; i >= 0; i--)
    t[i] = 0;
  lbsiz = 0;
  for (int i = 1; i <= _a; i++)
    if(ins(a[i])) {
      b[i] = 1;
    }
  if (cnt * (1 << lbsiz) == m) {
    int nd = n - lbsiz; // extra(the same as zero)
    for (int i = 1; i <= _a; i++) {
      if (b[i]) {
        std::cout << a[i] << ' ';
      }
      int up = std::min(nd, cnt - (b[i] || a[i] == 0));
      nd -= up;
      for (int j = 1; j <= up; j++)
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << -1 << '\n';
    throw 0;
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    try {
      work();
    } catch(int) {

    }
  }
  return 0;
}
