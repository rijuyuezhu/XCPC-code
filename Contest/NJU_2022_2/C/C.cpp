#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
using ll = long long;
using db = double;
const int MAXN = 1e6 + 5;
const int MAXV = 1 << 24;
const db PI = acos(-1.0);
const db eps = 1e-6;
int n, m;
struct cp {
   db x, y;
   cp(db x = 0, db y = 0) : x(x), y(y) {}
};
cp operator + (const cp &a, const cp &b) {return cp(a.x + b.x, a.y + b.y);}
cp operator - (const cp &a, const cp &b) {return cp(a.x - b.x, a.y - b.y);}
cp operator * (const cp &a, const cp &b) {return cp(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);}
int glim(int n) {
   int lim = 1;
   for(; lim <= n; lim <<= 1);
   return lim;
}
int tr[MAXN];
void tpre(int lim) {
   for(int i = 0; i < lim; i++)
      tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void DFT(cp f[], int lim) {
   tpre(lim);
   for(int i = 0; i < lim; i++)
      if(i < tr[i])
         swap(f[i], f[tr[i]]);
   for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) {
      cp w0 = cp(cos(2 * PI / l), sin(2 * PI / l));
      for(int i = 0; i < lim; i += l) {
         cp wn = cp(1, 0);
         for(int j = i; j < i + k; j++, wn = wn * w0) {
            cp tt = wn * f[j+k];
            f[j+k] = f[j] - tt;
            f[j] = f[j] + tt;
         }
      }
   }
}
void IDFT(cp f[], int lim) {
   DFT(f, lim); reverse(f + 1, f + lim);
   for(int i = 0; i < lim; i++) f[i].x /= lim, f[i].y /= lim;
}
int n, m, mxv;
cp a[MAXV], b[MAXV], tmp[MAXV];
void getarr(cp f[]) {
   int lim = glim(mxv << 1);
   for(int i = 0; i < mxv; i++)
      tmp[i] = f[mxv - i - 1];
   DFT(f, lim); DFT(tmp, lim);
   for(int i = 0; i < lim; i++) f[i] = f[i] * tmp[i];
   IDFT(f, lim);
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i++) {
      int v; scanf("%d", &v);
      mxv = max(mxv, v);
      a[v].x++;
   }
   for(int i = 1; i <= m; i++) {
      int v; scanf("%d", &v);
      mxv = max(mxv, v);
      b[v].x++;
   }
   mxv++;
   getarr(a);
   getarr(b);
   a[mxv - 1].x -= n;
   b[mxv - 1].x -= n;
   int t = -1;
   for(int i = 0; i < mxv; i++)
      if(a[mxv - 1 + i].x > 1-eps && b[mxv - 1 + i].x > 1-eps) {
         t = i;
         break;
      }
   if(t == -1) {
      printf("-1\n");
      return 0;
   }

   return 0;
}