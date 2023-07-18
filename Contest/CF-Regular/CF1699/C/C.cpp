// https://codeforces.com/contest/1699/problem/C

#include<cstdio>
#include<algorithm>
const int MOD = 1e9+7;
const int MAXN = 1e5+5;
struct mint {
   int v;
   mint(int x=0) :v(x) {}
};
mint operator + (mint a, mint b) {a.v += b.v; if(a.v >=MOD) a.v -= MOD; return a;}
mint operator - (mint a, mint b) {a.v -= b.v; if(a.v < 0) a.v += MOD; return a;}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % MOD;}
int n;
mint ans;
int l, r, a[MAXN], pos[MAXN];
namespace BIT {
   int t[MAXN];
   void clear() {
      for(int i = 1; i <= n; i++) t[i] = 0;
   }
   void add(int x, int v) {
      for(int i = x; i <= n; i += i & (-i)) t[i] += v;
   }
   int sum(int x) {
      int s = 0;
      for(int i = x; i; i -= i & (-i)) s += t[i];
      return s;
   }
   int sum(int l, int r) {
      return sum(r) - sum(l-1);
   }
}
void work() {
   scanf("%d", &n);
   ans = 1; l = n+1; r = 0;
   BIT::clear();
   for(int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      pos[a[i]] = i;
   }
   for(int i = 0; i < n; i++) {
      int p = pos[i];
      if(l <= p && p <= r) {
         int s = r-l+1-BIT::sum(l, r);
         ans = ans * s;
      } else {
         l = std::min(l ,p);
         r = std::max(r, p);
      }
      BIT::add(p, 1);
   }
   printf("%d\n", ans.v);
}
int main() {
   int t; scanf("%d", &t);
   for(int i = 1; i <= t; i++) work();
   return 0;
}