/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-04 16:41:24
 * @Description: https://www.luogu.com.cn/problem/SP1026
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}

int main() {
   int t = read();
   while(t--) {
      int n = read(); 
      db ans = 0.0;
      for(int i = 1; i <= n; i++) ans += (db)n / i;
      printf("%.2lf\n", ans);
   }
   return 0;
}