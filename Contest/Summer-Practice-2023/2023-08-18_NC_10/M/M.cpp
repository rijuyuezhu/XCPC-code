#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using i64 = long long;
std::string A, B, C;
int iA, iB, iC;
char tmp;
int converttoint(const std::string &s) {
  std::stringstream sst;
  int x;
  sst << s;
  sst >> x;
  return x;
}
std::string converttostring(int x) {
  std::stringstream sst;
  std::string s;
  sst << x;
  sst >> s;
  return s;
}
void output(int a, int b, int c) {
  std::cout << "Yes" << '\n' << a << " + " << b << " = " << c << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> A >> tmp >> B >> tmp >> C;
  iA = converttoint(A);
  iB = converttoint(B);
  iC = converttoint(C);
  if (iA + iB == iC) {
    output(iA, iB, iC);
    return 0;
  }
  std::string tA = converttostring(iC-iB);
  for (int i = 0; i < (int)tA.length(); i++) {
    std::string ttA = tA;
    ttA.erase(i, 1);
    if (A == ttA) {
      output(iC-iB, iB, iC);
      return 0;
    }
  }
  std::string tB = converttostring(iC-iA);
  for (int i = 0; i < (int)tB.length(); i++) {
    std::string ttB = tB;
    ttB.erase(i, 1);
    if (B == ttB) {
      output(iA, iC-iA, iC);
      return 0;
    }
  }
  std::string tC = converttostring(iA+iB);
  for (int i = 0; i < (int)tC.length(); i++) {
    std::string ttC = tC;
    ttC.erase(i, 1);
    if (C == ttC) {
      output(iA, iB, iA+iB);
      return 0;
    }
  }
  std::cout << "No" << '\n';
  return 0;
}
