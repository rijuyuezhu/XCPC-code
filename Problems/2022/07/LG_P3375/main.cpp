/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 16:51:16
 * @Description: https://www.luogu.com.cn/problem/P3375
 * @Tag: 字符串，KMP
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXL = 1e6 + 5;
char s[MAXL], t[MAXL]; //t is format string
int _s, _t, nxt[MAXL];
int main() {
   scanf("%s%s", s+1, t+1);
   _s = strlen(s+1); _t = strlen(t+1);
   for(int i = 2, j = 0; i <= _t; i++) {
      while(j && t[i] != t[j+1]) j = nxt[j];
      if(t[i] == t[j+1]) j++;
      nxt[i] = j;
   }
   for(int i = 1, j = 0; i <= _s; i++) {
      while(j && s[i] != t[j+1]) j = nxt[j];
      if(s[i] == t[j+1]) j++;
      if(j == _t) {
         printf("%d\n", i - j + 1);
      }
   }
   for(int i = 1; i <= _t; i++) printf("%d ", nxt[i]);
   printf("\n");
   return 0;
}