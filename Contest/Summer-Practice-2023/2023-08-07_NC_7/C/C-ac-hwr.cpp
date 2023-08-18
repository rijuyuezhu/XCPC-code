#include <iostream>
#include <algorithm>
using namespace std;
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
constexpr int B = 30;
int n, m, k, b[MAXN], t[B], cnt[B], ans;

void error() {
  cout << -1 << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
      cin >> b[i];
    }
    for (int j = 0; j < B; j++)
      t[j] = -1, cnt[j] = 0;
    for (int i = 1; i < n; i++) {
      int x = b[i], flag = 0;
      for (int j = B-1; j >= 0; j--)
        if ((x >> j) & 1) {
          if (!flag) {
            if (t[j] != -1 && t[j] != cnt[j]) {
              error();
              goto NXT;
            } else {
              t[j] = cnt[j];
            }
            flag = 1;
          }
          cnt[j] ^= 1;
        }
    }
    m = 0;
    for (int j = 0; j < B; j++)
      if (t[j] == -1) 
        m++;
    if (k > (1 << m)) {
      error();
      goto NXT;
    }
    for (int j = B-1; j >= 0; j--)
      if (t[j] == -1) {
        if (k <= (1 << (m-1)))
          t[j] = 0;
        else {
          t[j] = 1;
          k -= 1 << (m-1);
        }
        m--;
      }
    ans = 0;
    for (int j = 0; j < B; j++)
      ans |= (t[j] << j);
    cout << ans << ' ';
    for (int i = 1; i < n; i++) {
      ans ^= b[i];
      cout << ans << ' ';
    }
    cout << '\n';
  NXT:
    ;
  }
  return 0;
}
