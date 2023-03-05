/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-16 12:36:33
 * @Description: https://www.luogu.com.cn/problem/P2613
 * @Tag: 有理数取余，exgcd，扩展欧几里得，同余
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
const int P = 19260817;
ll readmodp() {
   ll x = 0; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar());
   for(; ch >= '0' && ch <= '9'; ch = getchar()) {
      x = x * 10 + int(ch - '0');
      if(x > 1e16) x %= P;
   }
   return x % P;
}
int a, b;
int gcd(int a, int b) {
   return !b ? a : gcd(b, a % b);
}
void exgcd(int a, int b, int &x, int &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int main() {
   a = readmodp();
   b = readmodp();
   int A = b, B = P, C = a, G = gcd(A, B);
   if(C % G != 0) {
      printf("Angry!\n");
      return 0;
   }
   int x, y, st = B / G;
   exgcd(A, B, x, y);
   x = ((1ll * x * (C / G)) % st + st) % st;
   printf("%d\n", x);
   return 0;
}