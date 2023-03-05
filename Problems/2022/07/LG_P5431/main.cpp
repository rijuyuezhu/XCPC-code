/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 22:51:17
 * @Description: https://www.luogu.com.cn/problem/P5431
 * @Tag: 逆元，数论
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
const int MAXN = 5e6 + 5;
int n, p, k, a[MAXN], s[MAXN], siv[MAXN], ans;
void exgcd(int a, int b, int &x, int &y) {
   if(!b) {x = 1, y = 0;}
   else {exgcd(b, a % b, y, x); y -= a / b * x;}
}
int inv(int a) {
   int x, y;
   exgcd(a, p, x, y);
   return (x % p + p) % p;   
}
int main() {
   n = read(); p = read(); k = read();
   s[0] = 1;
   for(int i = 1; i <= n; i++) {
      a[i] = read();
      s[i] = 1ll * s[i-1] * a[i] % p;
   }
   siv[n] = inv(s[n]);
   for(int i = n-1; i >= 1; i--)
      siv[i] = 1ll * siv[i+1] * a[i+1] % p;
   for(int i = 1, bas = k; i <= n; i++, bas = 1ll * bas * k % p) {
      ans = (ans + 1ll * siv[i] * s[i-1] % p * bas) % p;
   }
   printf("%d\n", ans);
   return 0;
}