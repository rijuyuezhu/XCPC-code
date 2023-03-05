/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:25:19
 * @Description: https://www.luogu.com.cn/problem/P1226
 * @Tag: 快速幂
*/


#include<cstdio>

int qpow(int a, int b, int p) {
   int ret = 1;
   for(; b; b >>= 1, a = (1ll * a * a) % p)
      if(b & 1) ret = (1ll * ret * a) % p;
   return ret;
}
int main() {
   int a, b, p;
   scanf("%d%d%d", &a, &b, &p);
   printf("%d^%d mod %d=%d\n", a, b, p, qpow(a, b, p));
   return 0;
}
