/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-04 16:52:59
 * @Description: https://www.luogu.com.cn/problem/P1654
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 1e5 + 5;
int n; 
db p[MAXN], a[MAXN], b[MAXN], c[MAXN];
int main() {
   n = read();
   for(int i = 1; i <= n; ++i) scanf("%lf", &p[i]);
   for(int i = 1; i <= n; ++i) {
      a[i] = p[i] * (a[i-1] + 1);
      b[i] = p[i] * (b[i-1] + 2 * a[i-1] + 1);
      c[i] = c[i-1] + (3 * b[i-1] + 3 * a[i-1] + 1) * p[i];
   }
   printf("%.1lf\n", c[n]);
   return 0;
}