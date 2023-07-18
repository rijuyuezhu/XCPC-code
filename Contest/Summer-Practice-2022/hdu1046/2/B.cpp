/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 12:09:31
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1046&pid=1002
 * @Tag: DP，状压
*/
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 18, MAXU = 1 << 18;
int n, U, t[MAXN], len[MAXN], st[MAXU];
ll f[MAXU], H;
vector<ll> d[MAXN];
void clear() {
}
bool check(int tim) {
   for(int i = 0; i <= U; i++) f[i] = 0;
   for(int i = 1; i <= U; i++) {
      for(int j = 0; j < n; j++) 
         if((i >> j) & 1) {
            int k = i ^ (1 << j);
            f[i] = max(f[i], f[k]);
            int us = min(len[j], tim - st[k] + 1);
            if(us <= 0) continue;
            f[i] = max(f[i], f[k] + d[j][us-1]);
         }
   }
   return f[U] >= H;
}
void work() {
   scanf("%d%lld", &n, &H);
   U = (1 << n) - 1;
   for(int i = 0; i < n; i++) {
      scanf("%d%d", &t[i], &len[i]);
      d[i].resize(len[i]);
      for(int j = 0; j < len[i]; j++) {
         scanf("%lld", &d[i][j]);
         if(j > 0) d[i][j] += d[i][j-1];
      }
   }
   st[0] = 0;
   for(int i = 1; i <= U; i++) {
      for(int j = 0; j < n; j++) {
         if((i >> j) & 1) {
            st[i] = st[i ^ (1 << j)] + t[j];
            break;
         }
      }
   }
   int l = 0, r = 3000001, ans = -1;
   while(l <= r) {
      int m = (l + r) >> 1;
      if(check(m)) {
         ans = m; r = m - 1;
      } else l = m + 1;
   }
   printf("%d\n", ans);
}
int main() {
   #ifdef LOCAL
   freopen("main.in", "r", stdin);
   #endif
   int t; scanf("%d", &t);
   for(int i = 1; i <= t; i++) work();
}
