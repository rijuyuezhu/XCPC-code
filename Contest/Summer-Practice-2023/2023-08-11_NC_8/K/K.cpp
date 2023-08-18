#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 205;
int n, m, a[MAXN][MAXN], b[MAXN], ans, t[MAXN];
int tryfox() {
  int i1 = -1, i2 = -1;
  for (int i = 1; i <= n; i++)
    if (a[i][1] != (i-1) * n + 1) {
      if (i1 == -1)
        i1 = i;
      else if (i2 == -1)
        i2 = i;
      else 
        return 0;
    }
  if (i1 == -1 || i2 == -1)
    return 0;
  for (int j = 1; j <= m; j++)
    std::swap(a[i1][j], a[i2][j]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i][j] != (i-1) * n + j)
        return 0;
  return 1;
}
void msort(int L, int R) {
  if (L == R)
    return ;
  int M = (L + R) >> 1;
  msort(L, M); msort(M+1, R);
  int i = L, j = M+1, k = L;
  while (i <= M && j <= R) {
    if (b[i] < b[j])
      t[k++] = b[i++];
    else {
      t[k++] = b[j++];
      ans += M - i + 1;
    }
  }
  while (i <= M)
    t[k++] = b[i++];
  while (j <= R)
    t[k++] = b[j++];
  for (i = L; i <= R; i++)
    b[i] = t[i];
}
void work() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      std::cin >> a[i][j];
  if (n >= 3 && m >= 3) {
    if (tryfox()) 
      std::cout << "FOX" << '\n';
    else 
      std::cout << "NSFW" << '\n';
  } else if (n >= 3) { // m == 2
    int flag1 = 1, flag2 = 1;
    for (int i = 1; i <= n; i++) {
      if (a[i][1] + 1 != a[i][2])
        flag1 = 0;
      if (a[i][1] - 1 != a[i][2])
        flag2 = 0;
    }
    ans = 0;
    for (int i = 1; i <= n; i++)
      b[i] = a[i][1];
    msort(1, n);
    std::cout << ((flag1 && ans % 2 == 1 || flag2 && ans % 2 == 0) ? "FOX" : "NSFW") << '\n';
  } else if (m >= 3) { // n = 2
    int flag1 = 1, flag2 = 1;
    for (int j = 1; j <= m; j++) {
      if (a[1][j] + m != a[2][j])
        flag1 = 0;
      if (a[1][j] - m != a[2][j])
        flag2 = 0;
    }
    ans = 0;
    for (int j = 1; j <= m; j++) 
      b[j] = a[1][j];
    msort(1, m);
    std::cout << ((flag1 && ans % 2 == 0 || flag2 && ans % 2 == 1) ? "CAT" : "NSFW") << '\n';

  } else {//n = m = 2
    int role = 0, win = -1;
    for (int i = 0; i < 4; i++) {
      if (i & 1) {//cat
        std::swap(a[1][1], a[1][2]);
        std::swap(a[2][1], a[2][2]);
      } else {//Fox
        std::swap(a[1][1], a[2][1]);
        std::swap(a[1][2], a[2][2]);
      }
      if (a[1][1] == 1 && a[1][2] == 2 && a[2][1] == 3 && a[2][2] == 4) {
        win = role;
        break;
      }
      role ^= 1;
    }
    switch(win) {
    case -1:
      std::cout << "NSFW" << '\n';
      break;
    case 0:
      std::cout << "FOX" << '\n';
      break;
    case 1:
      std::cout << "CAT" << '\n';
    }
  }

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
