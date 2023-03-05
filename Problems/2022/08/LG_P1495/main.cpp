/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-16 15:46:44
 * @Description: https://www.luogu.com.cn/problem/P1495
 * @Tag: 中国剩余定理（CRT），数论
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
const int MAXN = 15;
int n;
ll b[MAXN], m[MAXN], prod_m, ans;
ll mul(ll a, ll b, ll M) {
   ll c = (long double)a / M * b;
   ll d = (unsigned long long)a * b- (unsigned long long)c * M;
   return d;
}
void exgcd(ll a, ll b, ll &x, ll &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a, ll M) {
   ll x, y;
   exgcd(a, M, x, y);
   return (x % M + M) % M;
}
int main() {
   n = read();
   prod_m = 1;
   for(int i = 1; i <= n; i++) {
      m[i] = read(), b[i] = read();
      prod_m *= m[i];
   }
   ans = 0;
   for(int i = 1; i <= n; i++) {
      ll M = prod_m / m[i];
      ans = (ans + mul(mul(b[i], inv(M, m[i]), m[i]), M, prod_m)) % prod_m;
   }
   printf("%lld\n", ans);
   return 0;
}