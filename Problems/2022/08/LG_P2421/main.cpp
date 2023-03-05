/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-16 15:14:26
 * @Description: https://www.luogu.com.cn/problem/P2421
 * @Tag: 数论，同余方程，
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
const int MAXN = 16;
const int MAXL = 1e6 + 5;
int n, c[MAXN], p[MAXN], l[MAXN];
int gcd(int a, int b) {
   return !b ? a : gcd(b, a % b);
}
void exgcd(int a, int b, int &x, int &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int calc(int A, int B, int C) {
   if(A < 0) A *= -1, C *= -1;
   if(B < 0) B *= -1;
   int G = gcd(A, B);
   if(C % G != 0) return MAXL;//no root
   int x, y, st = B / G;
   exgcd(A, B, x, y);
   return ((1ll * x * (C / G)) % st + st) % st;
}
bool check(int m) {
   for(int i = 1; i <= n; i++)
      for(int j = i+1; j <= n; j++)
         if(calc(p[i] - p[j], m, c[j] - c[i]) <= min(l[i], l[j]))
            return 0;
   return 1;
}
int main() {
   n = read();
   int mxc = 0;
   for(int i = 1; i <= n; i++) {
      c[i] = read(), p[i] = read(), l[i] = read();
      mxc = max(mxc, c[i]);
   }
   for(int i = mxc; i <= 1000000; i++) 
      if(check(i)) {
         printf("%d\n", i);
         return 0;
      }
   return 0;
}