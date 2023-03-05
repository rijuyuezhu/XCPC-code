#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
const int MAXN = 5005;
const int P = 998244353;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
   int v;
   mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
int n, k, r, a[MAXN], c[MAXN];
mint f[MAXN][MAXN];
int main() {
   scanf("%d%d%d", &n, &k, &r);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   for(int i = 1; i <= n; i++) {
      c[i] = 0;
      for(int j = 1; j < i; j++) {
         if(a[j] + r <= a[i])
            c[i] = j;
         else 
            break;
      }
   }
   f[0][0] = 1;
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= k; j++) {
         f[i][j] = f[i-1][j-1];
         if(c[i] - (i - j - 1) > 0)
            f[i][j] = f[i][j] + (c[i] - (i - j - 1)) * f[i-1][j];
      }
   printf("%d\n", f[n][k].v);
   return 0;
}