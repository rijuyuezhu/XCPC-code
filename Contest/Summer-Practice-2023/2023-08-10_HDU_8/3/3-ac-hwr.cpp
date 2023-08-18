#include <iostream>
#include <algorithm>
using i64 = long long;
using i128 = __int128;
constexpr int MAXM = 105;
int m;
i128 p[MAXM], q[MAXM], n, ans;
void exgcd(i128 a, i128 b, i128 &x, i128 &y) {
  if (!b) x = 1, y = 0;
  else exgcd(b, a % b, y, x), y -= a / b * x;
}
i128 inv(i128 a, i128 p) {
  i128 x, y;
  exgcd(a, p, x, y);
  return (x % p + p) % p;
}
i128 qpow(i128 a, i128 n, i128 M) {
  i128 ret = 1;
  for (; n; n >>= 1, a = a * a % M)
    if (n & 1)
      ret = ret * a % M;
  return ret;
}
void work() {
  n = 1; 
  std::cin >> m;
  for (int i = 1; i <= m; i++) {
    i64 vp, vq;
    std::cin >> vp >> vq;
    p[i] = vp;
    q[i] = vq;
    n *= p[i];
  }
  ans = 0;
  for (int i = 1; i <= m; i++) {
    i128 M = n / p[i];
    ans = (ans + ((q[i] % p[i]) * inv(M, p[i]) % p[i]) * M % n) % n;
  }
  if (ans == 0)
    ans += n;
  int flag = 1;
  for (int i = 1; i <= m; i++)
    if (qpow(ans, p[i], n) != q[i]) {
      flag = 0;
      break;
    }
  if (flag)
    std::cout << (i64)ans << '\n';
  else 
    std::cout << -1 << '\n';
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
