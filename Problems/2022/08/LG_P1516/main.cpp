/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-02 08:46:42
 * @Description: https://www.luogu.com.cn/problem/P1516
 * @Tag: 同余方程，扩展欧几里得
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
int x, y, m, n, L, A, B, C;
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
void exgcd(int a, int b, int &x, int &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int main() {
   x = read(), y = read(), m = read(), n = read(), L = read();
   A = m - n; B = L; C = y - x;
   if(A < 0) {
      A *= -1; C *= -1;
   }
   int D = gcd(A, B);
   if(C % D) {
      printf("Impossible\n");
      return 0;
   }
   int X, Y;
   exgcd(A, B, X, Y);
   int stB = B / D;
   X = (1ll * X * (C / D) % stB + stB) % stB;
   printf("%d\n", X);
   return 0;
}