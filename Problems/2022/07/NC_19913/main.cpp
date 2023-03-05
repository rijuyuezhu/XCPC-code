/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-28 09:18:32
 * @Description: https://ac.nowcoder.com/acm/problem/19913
 * @Tag: 前缀和
*/

#include<cstdio>

typedef long long ll;
const int MAXN = 1e5 + 5;
int n, b, a[MAXN], cnt1[MAXN * 2], cnt2[MAXN * 2];
ll ans;
int main() {
   scanf("%d%d", &n, &b);
   for(int i = 1; i <= n; i++) {
      int v;
      scanf("%d", &v);
      if(v > b) a[i] = 1;
      else if(v == b) a[i] = 0;
      else a[i] = -1;
      a[i] += a[i-1];
   }
   for(int i = 0; i <= n; i++)
      if(i & 1)
         cnt1[a[i]+MAXN]++;
      else
         cnt2[a[i]+MAXN]++;
   for(int i = -n; i <= n; i++)
      ans += cnt1[i+MAXN] * cnt2[i+MAXN];
   printf("%lld\n", ans);
   return 0;
}