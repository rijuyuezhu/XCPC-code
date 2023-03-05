/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-03 07:33:38
 * @Description: https://www.luogu.com.cn/problem/P3389
 * @Tag: 高斯消元，线性代数
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
constexpr int MAXN = 105;
constexpr double eps = 1e-8;
int n;
db a[MAXN][MAXN];
int main() {
   n = read();
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n+1; j++)
         a[i][j] = read();
   for(int i = 1; i <= n; i++) {
      int num = i;
      for(int j = i+1; j <= n; j++)
         if(abs(a[j][i]) > abs(a[num][i])) {
            num = j;
         }
      if(num != i)
         for(int j = i; j <= n+1; j++) 
            swap(a[i][j], a[num][j]);
      if(abs(a[i][i]) < eps) {
         printf("No Solution\n");
         return 0;
      }
      /**
       * a[i][i]
       * a[j][i]
      **/
      for(int j = i+1; j <= n; j++) {
         double t = a[j][i] / a[i][i];
         for(int k = i; k <= n+1; k++)
            a[j][k] -= t * a[i][k];
      }
   }
   for(int i = n; i >= 1; i--) {
      for(int j = i+1; j <= n; j++)
         a[i][n+1] -= a[j][n+1] * a[i][j];
      a[i][n+1] /= a[i][i];
   }
   for(int i = 1; i <= n; i++) printf("%.2lf\n", a[i][n+1]);
   return 0;
}