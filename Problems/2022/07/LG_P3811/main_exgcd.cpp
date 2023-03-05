/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 06:56:53
 * @Description: https://www.luogu.com.cn/problem/P3811
 * @Tag: 乘法逆元，扩展欧拉定理
*/
#include<cstdio>
int n, p;
int MOD(int v) {return v >= p ? v-p : v;}
void exgcd(int a, int b, int& x, int& y) {
   if(!b) x = 1, y = 0; // ax+0y=gcd(a,0)=a
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int inv(int v) {
   int x, y;
   exgcd(v, p, x, y);
   return MOD(x % p + p);
}
int main() {
   scanf("%d%d", &n, &p);
   for(int i = 1; i <= n; i++) {
      printf("%d\n", inv(i));
   }
   return 0;
}