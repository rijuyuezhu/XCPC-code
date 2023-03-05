/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:29:24
 * @Description: https://www.luogu.com.cn/problem/P3383
 * @Tag: 线性筛质数
*/

#include<cstdio>
const int MAXN = 1e8+5;
int n, q;
bool npr[MAXN];
int pr[MAXN], _pr;
void get_prime(int n) {
   npr[1] = 1; _pr = 0;
   for(int i = 2; i <= n; i++) {
      if(!npr[i]) {
         pr[++_pr] = i;
      }
      for(int j = 1, _lim = n / i; j <= _pr && pr[j] <= _lim; j++) {
         int k = i * pr[j];
         npr[k] = 1;
         if(i % pr[j] == 0) break;
      }
   }
}
int main() {
   scanf("%d%d", &n, &q);
   get_prime(n);
   for(int i = 1; i <= q; i++) {
      int t; scanf("%d", &t);
      printf("%d\n", pr[t]);
   }
   return 0;
}