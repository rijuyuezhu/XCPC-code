#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using i64 = long long;
constexpr int MAXN = 2005;
int n, a[MAXN];
char qry(int x) {
  std::cout << "? " << x << '\n';
  std::cout.flush();
  char ans;
  std::cin >> ans;
  return ans;
}
void response() {
  std::cout << "! ";
  for (int i = 1; i <= n; i++)
    std::cout << a[i] << ' ';
  std::cout << '\n';
  std::cout.flush();
}
void dfs(const std::vector<int> &in, int L, int R) {
  if (in.empty())
    return;
  else if (in.size() == 1u) {
    a[in[0]] = L;
    return;
  } else {
    int x = rand() % int(in.size());
    while (qry(in[x]) != '=')
      ;
    std::vector<int> l, r;
    for (auto i : in)
      if (i != in[x]) {
        char res = qry(i);
        if (res == '<') {
          l.push_back(i);
        } else {
          r.push_back(i);
        }
        qry(in[x]);
      }
    a[in[x]] = L + (int)l.size();
    dfs(l, L, L + (int)l.size() - 1);
    dfs(r, L + (int)l.size() + 1, R);
  }
}
void work() {
  std::cin >> n;
  std::vector<int> in;
  for (int i = 1; i <= n; i++)
    in.push_back(i);
  dfs(in, 1, n);
  response();
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  srand(time(0));
  int T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
