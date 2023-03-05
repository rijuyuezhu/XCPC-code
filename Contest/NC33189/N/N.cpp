/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 12:32:02
 * @Description: https://ac.nowcoder.com/acm/contest/33189/N
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
const int B = 15;
int n, cnt[B], a[MAXN];
ll x, sum, y;
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
int main() {
   n = read();
   for(int i = 1; i <= n; i++) {
      int v = read();
      for(int j = 0; j < B; j++)
         if((v >> j) & 1) cnt[j]++;
   }
   for(int i = 1; i <= n; i++) {
      for(int j = 0; j < B; j++)
         if(cnt[j]) a[i] |= 1 << j, --cnt[j];
   }
   for(int i = 1; i <= n; i++) {
      x += 1ll * a[i] * a[i];
      sum += a[i];
   }
   x = x * n - sum * sum;
   y = 1ll * n * n;
   ll g = gcd(x, y);
   x /= g; y /= g; printf("%lld/%lld\n", x, y);
   return 0;
}