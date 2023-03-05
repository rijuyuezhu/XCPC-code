/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 16:59:28
 * @Description: https://www.luogu.com.cn/problem/P3368
 * @Tag: 数据结构，树状数组
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
const int MAXN = 500005;
int n, m;
int a[MAXN];
namespace BIT {
   int t[MAXN];
   void build() {
      for(int i = 1; i <= n; i++)
         t[i] = a[i] - a[i - (i & -i)];
   }
   void add(int x, int v) {
      for(int i = x; i <= n; i += i & -i) t[i] += v;
   }
   int sum(int x) {
      int ret = 0;
      for(int i = x; i; i -= i & -i) ret += t[i];
      return ret;
   }
}
int main() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++) a[i] = read();
   BIT::build();
   for(int i = 1; i <= m; i++) {
      int opt = read();
      if(opt == 1) {
         int x = read(), y = read(), k = read();
         BIT::add(x, k); BIT::add(y+1, -k);
      } else {
         int x = read();
         printf("%d\n", BIT::sum(x));
      }
   }
   return 0;
}