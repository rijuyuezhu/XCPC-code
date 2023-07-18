/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 12:48:53
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1046&pid=1003
 * @Tag: 
*/
#include<string>
#include<iostream>
using namespace std;
string s;
int main() {
   ios::sync_with_stdio(0);
   int t; cin >> t; getline(cin, s);
   for(int i = 1; i <= t; i++) {
      getline(cin, s);
      cout << char(s[0] - 'a' + 'A');
      for(int i = 1; i < s.length()-1; i++)
         if(s[i] == ' ') cout << char(s[i+1] - 'a' + 'A');
      cout << '\n';
   }
   return 0;
}