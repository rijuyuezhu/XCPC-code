#include <iostream>
#include <algorithm>
using i64 = long long;
constexpr int MAXN = 5e5 + 5;
int n, a[MAXN], cnt[MAXN];

void work() {
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    cnt[i] = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    cnt[a[i]]++;
  }
  int mni = 0, nze = -1;
  for (int i = 1; i <= n; i++) {
    if (cnt[i] > cnt[mni])
      mni = i;
    if (cnt[i] != 0 && nze == -1)
      nze = i;
  }
  if (mni == nze)
    std::cout << "YES" << '\n';
  else 
    std::cout << "NO" << '\n';
  
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--)
    work();

  return 0;
}
