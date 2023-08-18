#include <iostream>
#include <algorithm>
using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    i64 n, ans = 0;
    cin >> n;
    for (i64 i = i64(1e9), d = 10; i >= 1; i /= 10, d--) {
      if (n >= i) {
        ans += d * (n - i + 1);
        n = i-1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
