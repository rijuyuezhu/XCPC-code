#include <iostream>
#include <algorithm>
#include <string>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
int n, m;
std::string a[MAXN];
int cnt1(const std::string &s, int l, int r) {
  int cnt = 0;
  for (int i = l; i <= r; i++)
    if (s[i] == '1')
      ++cnt;
  return cnt;
}
void case1() {
  int ret = 0;
  for (int i = 1; i <= n; i++) {
    ret ^= (cnt1(a[i], 1, m) & 1);
  }
  if (ret & 1)
    std::cout << "Alice" << '\n';
  else 
    std::cout << "Bob" << '\n';
}
void case2() {
  int ret = 0, chan = 0;
  int k = m / 2 + 1;
  for (int i = 1; i <= n; i++) {
    int L = cnt1(a[i], 1, k-1), R = cnt1(a[i], k+1, m), M = (a[i][k] == '1');
    if (L == 0 || R == 0){
      ret ^= (L + R) & 1;
    } else if (M == 1 && (L == 1 || R == 1)) {//special: can change
      chan++;
      ret ^= (L + R) & 1;
    } else {
      ret ^= (M + L + R) & 1;
    }
  }
  if (chan & 1)
    std::cout << "Alice" << '\n';
  else {
    if (ret & 1)
      std::cout << "Alice" << '\n';
    else 
      std::cout << "Bob" << '\n';
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    a[i] = ' ' + a[i];
  }
  if (m % 2 == 0)
    case1();
  else 
    case2();
  
  return 0;
}
