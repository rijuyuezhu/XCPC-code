/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-26 11:07:53
 * @Description: https://www.luogu.com.cn/problem/P1641
 * @Tag: Catalan，逆元
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
const int P = 20100403;
const int MAXN = 1e7 + 5;
struct mint {
   int v;
   mint(int v = 0) : v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, int n=P-2) {
   mint ret = 1;
   for(; n; n >>= 1, a = a * a) 
      if(n & 1) ret = ret * a;
   return ret;
}

int n, m;
mint fac[MAXN], ifac[MAXN];
void init_fac(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i++)
      fac[i] = fac[i-1] * i;
   ifac[n] = qpow(fac[n]);
   for(int i = n-1; i >= 0; i--)
      ifac[i] = ifac[i+1] * (i+1);
}
mint C(int n, int m) {
   if(n < 0 || m < 0 || n < m) return 0;
   return fac[n] * ifac[m] * ifac[n-m];
}
int main() {
   n = read(), m = read();
   init_fac(n + m);
   printf("%d\n", (C(n+m, m) - C(n+m, m-1)).v);
   return 0;
}