/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:13:51
 * @Description: https://www.luogu.com.cn/problem/P3811
 * @Tag: 乘法逆元 线性1
*/
#include<cstdio>
const int MAXN = 3e6 + 5;
int n, p, iv[MAXN];
int main() {
   scanf("%d%d", &n, &p);
   iv[1] = 1;
   for(int i = 2; i <= n; i++) iv[i] = 1ll * (p - p / i) * iv[p % i] % p;
   for(int i = 1; i <= n; i++) printf("%d\n", iv[i]);
   return 0;
}