/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:28:56
 * @Description: https://www.luogu.com.cn/problem/P3382
 * @Tag: 三分
*/

#include<cstdio>

const int MAXN = 15;
const double eps = 1e-7;
int n;
double l, r, a[MAXN];
double f(double x) {
   double ret = 0;
   for(int i = 0; i <= n; i++) ret = ret * x + a[i];
   return ret;
}
int main() {
   scanf("%d%lf%lf", &n, &l, &r);
   for(int i = 0; i <= n; i++) scanf("%lf", &a[i]);
   while(r-l > eps) {
      double lm = l + (r-l) / 3.0;
      double rm = r - (r-l) / 3.0;
      double flm = f(lm), frm = f(rm);
      if(flm < frm) l = lm;
      else r = rm;
   }
   printf("%lf", l);
   return 0;
}