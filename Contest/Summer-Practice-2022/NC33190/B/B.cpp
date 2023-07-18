/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-01 12:04:14
 * @Description: https://ac.nowcoder.com/acm/contest/33190/B
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
const int MAXM = 1e5 + 5;
int n, m, a[MAXN], b[MAXN];
bool check(int k) {
   for(int i = 1; i <= n; i++) b[i] = a[i] + i * k;
   sort(b + 1, b + 1 + n);
   for(int i = 1; i <= k; i++) b[i] += b[i-1];
   return b[k] <= m;
}
int main() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++) a[i] = read();
   int l = 0, r = min(n, 60), ans = -1;
   while(l <= r) {
      int m = (l + r) >> 1;
      if(check(m)) {
         ans = m; l = m+1;
      } else r = m-1;
   }
   printf("%d\n", ans);
   return 0;
}