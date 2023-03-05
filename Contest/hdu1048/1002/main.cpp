/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-02 12:33:58
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1048&pid=1002
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
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
const ll P = 4179340454199820289ll, MAXM = 1e12+5;
const int MAXK = 2e6 + 5;
ll MOD(ll v) {return v >= P ? v - P : v;}
ll Add(ll x, ll y) {return MOD(x+y);}
ll Mns(ll x, ll y) {return MOD(x-y+P);}
ll Mul(ll x, ll y){
   #if 0
	ll z=(long double)x / P * y;
	ll res=(unsigned long long)x * y - (unsigned long long)z * P;
	return (res + P) % P;
   #else
   return (__int128_t)x * y % P;
   #endif
}
ll qpow(ll x, ll n) {
   ll ret = 1;
   for(; n; n >>= 1, x = Mul(x, x))
      if(n & 1) ret = Mul(ret, x);
   return ret;
}
const ll inv2 = qpow(2, P-2);
ll M, g[MAXK], w[MAXK], pr[MAXK], sp[MAXK], iv[MAXK];
int sM, ip[MAXK], tot, num, id1[MAXK], id2[MAXK];
void init(int n) {
   ip[1] = 1;
   for(int i = 2; i <= n; i++) {
      if(!ip[i]) {
         pr[++tot] = i;
         sp[tot] = Add(sp[tot-1], i);
      }
      for(int j = 1; j <= tot && i * pr[j] <= n; j++) {
         ip[i * pr[j]] = 1;
         if(i % pr[j] == 0) break;
      }
   }
}
ll S(ll x, int k) {
   if(pr[k] >= x) return 0;
   int t = x <= sM ? id1[x] : id2[M / x];
   ll ret = Mns(g[t], sp[k]);
   for(int j = k+1; j <= tot && pr[j] * pr[j] <= x; j++) {
      ll p = 1;
      for(int e = 1; p <= x / pr[j]; e++, p *= pr[j]) {
         ll pn = p * pr[j];
         ret = Add(ret, Mul(Mul(pn, iv[e]), Add(S(x / pn, j), int(e != 1))));
      }
   }
   return ret;
}
void work() {
   M = read(); sM = sqrt(M) + 5;
   tot = 0, num = 0;
   for(int i = 1; i <= sM; i++) ip[i] = 0;
   init(sM);
   for(ll i = 1, j; i <= M; i = j + 1) {
      ll t = M / i;
      j = M / t;
      w[++num] = t;
      g[num] = Mns((t & 1) ? Mul(t, (t+1)/2) : Mul(t/2, t+1), 1);
      if(t <= sM) id1[t] = num;
      else id2[M / t] = num;
   }
   for(int j = 1; j <= tot; j++) 
      for(int i = 1; i <= num && pr[j] * pr[j] <= w[i]; i++) {
         ll nxt = w[i] / pr[j]; int t = nxt <= sM ? id1[nxt] : id2[M / nxt];
         g[i] = Mns(g[i], Mul(pr[j], Mns(g[t], sp[j-1])));
      }
   printf("%lld\n", Mul(qpow(M, P-2), Add(S(M, 0), 1)));
}

int main() {
   for(int i = 1; i <= 100; i++) iv[i] = qpow(i, P-2);
   int T = read();
   while(T--) work();
   return 0;
}