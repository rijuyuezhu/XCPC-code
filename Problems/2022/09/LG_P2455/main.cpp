/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-03 11:02:46
 * @Description: https://www.luogu.com.cn/problem/P2455
 * @Tag: 高斯校园，线性方程组
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
constexpr int MAXN = 55;
constexpr db eps = 1e-6;
int n;
db a[MAXN][MAXN];
int main() {
   n = read();
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n+1; j++)
         a[i][j] = read();
   int r = 1;
   for(int c = 1; c <= n; c++) {
      int num = r;
      for(int i = r+1; i <= n; i++)
         if(abs(a[i][c]) > abs(a[num][c]))
            num = i;
      if(num != r)
         for(int i = c; i <= n+1; i++)
            swap(a[r][i], a[num][i]);
      if(abs(a[r][c]) < eps)
         continue;
      for(int i = r+1; i <= n; i++) {
         db k = a[i][c] / a[r][c];
         for(int j = c; j <= n+1; j++)
            a[i][j] -= k * a[r][j];
      }
      r++;
   }
   if(r <= n) { //[r,n] exist; then all are zero.
      for(int i = r; i <= n; i++)
         if(abs(a[i][n+1]) > eps) {
            printf("-1\n");
            return 0;
         }
      printf("0\n");
      return 0;
   }
   for(int i = n; i >= 1; i--) {
      for(int j = i+1; j <= n; j++)
         a[i][n+1] -= a[j][n+1] * a[i][j];
      a[i][n+1] /= a[i][i];
   }
   for(int i = 1; i <= n; i++)
      printf("x%d=%.2lf\n", i, (abs(a[i][n+1]) < eps ? eps : a[i][n+1]));
   return 0;
}