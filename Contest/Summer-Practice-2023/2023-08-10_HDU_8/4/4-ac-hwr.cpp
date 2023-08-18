#include <iostream>
#include <algorithm>
#include <string>
using i64 = long long;
constexpr int MAXN = 1e5 + 5;
std::string s;
int n;
void win(int r) {
  std::cout << r << '\n';
  throw 0;
}

void check(int role, int L, int R) {
  int lpos = -1, rpos = -1;
  for (int i = L; i < R; i += 2) {
    if (s[i] == '0' + role) {
      if (s[i+1] == '0' + role)
        win(role);
    } else {
      lpos = i-1;
      break;
    }
  }
  for (int i = R; i > L; i -= 2) {
    if (s[i] == '0' + role) {
      if (s[i-1] == '0' + role)
        win(role);
    } else {
      rpos = i;
      break;
    }
  }
  if (lpos == rpos) //including the case when both is -1
    win(-1);
  else 
    win(role^1);
}
void work() {
  std::cin >> n;
  std::cin >> s;
  int role = 0, L = 0, R = n-1;
  while (L <= R) {
    if (s[L] == '0' + role && s[R] == '0' + role) {
      check(role, L, R);
    } else if (s[L] == '0' + role)
      L++;
    else if (s[R] == '0' + role)
      R--;
    else 
      win(role^1);
    role ^= 1;
  }
  win(-1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    try {
      work(); 
    } catch(int) {}

  }
  return 0;
}
