#include <iostream>
#include <algorithm>
#include <string>
using i64 = long long;
std::string s, t, buf;
int n;
void work(int te) {
  std::cin >> s >> t;
  buf.clear();
  n = s.length();
  int diff = 0, delta = 0;
  for (int i = 0; i < n; i++)
    if (s[i] != t[i])
      diff++;
  for (int i = 0; i < n; i++)
    if (s[i] == t[i])
      buf.push_back('a');
    else {
      diff--;
      char c = 0;
      if (delta > diff)
        c = t[i];
      else if (delta < -diff)
        c = s[i];
      else if (delta < diff && delta > -diff)
        c = 'a';
      else if (delta == 0 && diff == 0) {
        if (s[i] != 'a' && t[i] != 'a')
          c = 'a';
        else if (s[i] != 'b' && t[i] != 'b')
          c = 'b';
        else
          c = 'c';
      } else if (delta == diff) { // c cannot == s[i]
        if (s[i] == 'a')
          c = 'b';
        else
          c = 'a';
      } else { // delta == -diff, c cannot == t[i]
        if (t[i] == 'a')
          c = 'b';
        else
          c = 'a';
      }
      buf.push_back(c);
      if (c == s[i]) 
        delta++;
      else if (c == t[i])
        delta--;
    }
  std::cout << "Case " << te << ": " << buf << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  for (int i = 1; i <= T; i++)
    work(i);
  return 0;
}
