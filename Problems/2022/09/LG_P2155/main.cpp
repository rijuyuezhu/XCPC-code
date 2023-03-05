/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-02 17:00:03
 * @Description: https://www.luogu.com.cn/problem/P2155
 * @Tag: 数论，欧拉函数
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
const int MAXN = 1e7 + 5;
int P;
int pr[MAXN], tot, fac[MAXN], pd_pd1[MAXN], ivpd_p[MAXN];
bool np[MAXN];
int qpow(int a, int n) {
   int ret = 1;
   for(; n; n >>= 1, a = 1ll * a * a % P)
      if(n & 1) ret = 1ll * ret * a % P;
   return ret;
}
void init(int n) {
   np[1] = 1;
   for(int i = 2; i <= n; i++) {
      if(!np[i])
         pr[++tot] = i;
      for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
         np[i * pr[j]] = 1;
         if(i % pr[j] == 0) break;
      }
   }
   fac[0] = 1;
   for(int i = 1; i <= n; i++)
      if(i == P) fac[i] = fac[i-1];
      else fac[i] = 1ll * fac[i-1] * i % P;
   pd_pd1[0] = ivpd_p[0] = 1;
   for(int i = 1; i <= tot; i++) {
      pd_pd1[i] = 1ll * pd_pd1[i-1] * (pr[i] - 1) % P;
      if(pr[i] == P)
         ivpd_p[i] = ivpd_p[i-1];
      else 
         ivpd_p[i] = 1ll * ivpd_p[i-1] * qpow(pr[i], P-2) % P;
   }
}
int main() {
   int t = read();
   P = read();
   init(1e7);
   for(int i = 1; i <= t; i++) {
      int n = read(), m = read();
      int id = upper_bound(pr + 1, pr + 1 + tot, m) - pr - 1; // id of the first num that <= m
      if(P <= m)
         printf("%lld\n", 1ll * fac[n] * pd_pd1[id] % P * ivpd_p[id] % P); 
      else if(P < n)
         printf("0\n");
      else if(P == n) {
         if(m == n) printf("%lld\n", 1ll * fac[n] * pd_pd1[id] % P * ivpd_p[id] % P);
         else printf("0\n");
      } else //P > n
         printf("%lld\n", 1ll * fac[n] * pd_pd1[id] % P * ivpd_p[id] % P);
   }
   return 0;
}

