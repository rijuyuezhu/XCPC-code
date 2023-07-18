/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-28 14:16:12
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1047&pid=1006
 * @Tag: 
*/
#include<cstdio>

const int MAXN = 1e5 + 5;
const double eps = 1e-6;
int n;
int a[MAXN];

double calc1() {
   double ans = 0.0, tmp;
   for(int i = 1; i <= n; i++) {
      tmp = a[i];
      if(ans < 100.0 - eps) {
         if(ans + tmp > 100.0 - eps) {
            double del = 100.0 - ans;
            ans = 100.0;
            tmp -= del;
         } else {
            ans += tmp;
            continue;
         }
      }
      if(ans < 200.0 - eps) {
         if(ans + tmp * 0.8 > 200.0 - eps) {
            double del = (200.0 - ans) / 0.8;
            ans = 200.0;
            tmp -= del;
         } else {
            ans += tmp * 0.8;
            continue;
         }
      }
      ans += tmp * 0.5;
   }
   return ans;
}
double calc2() {
   double ans = 0.0;
   for(int i = 1; i <= n; i++) {
      if(ans < 100.0 - eps) ans += a[i];
      else if(ans < 200.0 - eps) ans += a[i] * 0.8;
      else ans += a[i] * 0.5;
   }
   return ans;
}
void work() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   printf("%.3lf %.3lf\n", calc1(), calc2());
}
int main() {
   int t; scanf("%d", &t);
   while(t--) work();
   return 0;
}