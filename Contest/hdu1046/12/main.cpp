/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 13:44:38
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1046&pid=1012
 * @Tag: DP，转移优化
*/
#include<cstdio>
using namespace std;
const int P = 998244353;
const int MAXN = 6e5 + 5;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
   int v;
   mint(int v=0) :v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}

int n, p[MAXN], q[MAXN], s[MAXN], posp[MAXN], posq[MAXN];
int lst[MAXN][2];
mint f[MAXN][2];
mint get(int k, int i) {
   if(lst[i][k & 1] != k) return 0;
   else return f[i][k & 1];
}
void add(int k, int i, mint v) {
   if(lst[i][k & 1] != k) lst[i][k & 1] = k, f[i][k & 1] = v;
   else f[i][k & 1] = f[i][k & 1] + v;
}
void work() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) {
      scanf("%d", &p[i]);
      posp[p[i]] = i;
   }
   for(int i = 1; i <= n; i++) {
      scanf("%d", &q[i]);
      posq[q[i]] = i;
   }
   for(int i = 1; i <= 2 * n; i++) scanf("%d", &s[i]);
   for(int i = 0; i <= n; i++) lst[i][0] = lst[i][1] = -1;
   add(0, 0, 1);
   for(int k = 1; k <= 2 * n; k++) {
      int t;
      t = k - posq[s[k]]; 
      if(t >= 0) add(k, t, get(k-1, t));
      t = posp[s[k]];
      add(k, t, get(k-1, t-1));      
   }
   printf("%d\n", get(2 * n, n).v);
}
int main() {
   int t; scanf("%d", &t);
   while(t--) work();
   return 0;
}