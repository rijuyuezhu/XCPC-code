/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-15 17:47:43
 * @Description: https://codeforces.com/contest/1712/problem/D
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 1e5 + 5;
const int V = 1e9;
int n, k, a[MAXN], b[MAXN];
bool check(int d) {
   for(int i = 1; i <= n; i++) b[i] = a[i];
   int num = k;
   for(int i = 1; i <= n; i++)
      if(2 * b[i] < d) num--, b[i] = V;
   if(num < 0)
      return 0;
   else if(num == 0) {
      for(int i = 1; i < n; i++)
         if(b[i] >= d && b[i+1] >= d)
            return 1;
      return 0;
   } else if(num == 1) {
      for(int i = 1; i <= n; i++)
         if(b[i] >= d)
            return 1;
      return 0;
   } else   //num >= 2
      return 1;
}
void work() {
   n = read(), k = read();
   for(int i = 1; i <= n; i++) a[i] = read();
   int l = 1, r = V, ans = -1;
   while(l <= r) {
      int m = (l + r) >> 1;
      if(check(m)) {
         ans = m;
         l = m + 1;
      } else r = m - 1;
   }
   printf("%d\n", ans);
}
int main() {
   int t = read();
   while(t--) work();
   return 0;
}