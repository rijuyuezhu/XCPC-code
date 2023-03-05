/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 06:28:46
 * @Description: https://www.luogu.com.cn/problem/P3811
 * @Tag: 乘法逆元 费马小定理
*/
#include<cstdio>
int p, n;
struct mint {
   int v;
   mint(int v=0):v(v) {}
};
mint operator + (mint a, mint b) {return a.v + b.v >= p ? a.v + b.v - p : a.v + b.v;}
mint operator - (mint a, mint b) {return a.v - b.v < 0 ? a.v - b.v + p : a.v - b.v;}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % p;}
mint qpow(mint a, int n) {

   mint ret = 1;
   for(; n; n >>= 1, a = a * a)
      if(n & 1) ret = ret * a;
   return ret;
}
mint inv(mint a) {
   return qpow(a, p-2);
}
int main() {
   scanf("%d%d", &n, &p);
   for(int i = 1; i <= n; i++) printf("%d\n", inv(i).v);
   return 0;
}