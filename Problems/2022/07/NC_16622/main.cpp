/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-25 22:55:16
 * @Description: https://ac.nowcoder.com/acm/problem/16622
 * @Tag: 模拟
*/

#include<cstdio>
const int MAXN = 105;
int n, a[MAXN];
void print(int v, int c) {//v * x^c
   if(v == 0) return;
   else if(v > 0) {
      if(c != n) printf("+");
      if(v != 1 || c == 0) printf("%d", v);
   } else {
      if(v != -1 || c == 0) printf("%d", v);
      else printf("-");
   }
   if(c == 0) ;
   else if(c == 1) printf("x");
   else printf("x^%d", c);
}
int main() {
   scanf("%d", &n);
   for(int i = n; i >= 0; i--) scanf("%d", &a[i]);
   print(a[n], n);
   for(int i = n-1; i >= 0; i--) print(a[i], i);
   printf("\n");
   return 0;
}
