#include <ctime>
#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
int n, p[MAXN], t[MAXN];
i64 cnt;
void msort(int L, int R) {
  if (L == R)
    return ;
  int M = (L + R) >> 1;
  msort(L, M);
  msort(M+1, R);
  int i = L, j = M+1, k = L;
  while (i <= M && j <= R) {
    if (p[i] < p[j])
      t[k++] = p[i++];
    else {
      cnt += M - i + 1;
      t[k++] = p[j++];
    }
  }
  while (i <= M)
    t[k++] = p[i++];
  while (j <= R)
    t[k++] = p[j++];
  for (int i = L; i <= R; i++)
    p[i] = t[i];
}
void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> p[i];
  if (n == 1) {
    std::cout << 0 << ' ' << 1 << '\n';
    return ;
  }
  cnt = 0;
  msort(1, n);
  int mans = 0;
  if (cnt & 1) {
    mans = 2;
    std::cout << 2 << ' ';
  } else {
    mans = 0;
    std::cout << 0 << ' ';
  }
  for (int i = 4; i <= n; i <<= 1)
    mans |= i;
  mans |= 1;
  std::cout << mans << '\n';
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
