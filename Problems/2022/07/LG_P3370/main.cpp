/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:27:33
 * @Description: https://www.luogu.com.cn/problem/P3370
 * @Tag: 字符串哈希
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned int uint;
struct HASH {
   uint a, b;
   HASH(int a=0, int b=0) : a(a), b(b) {}
};
HASH operator + (HASH x, HASH y) {
   return HASH(x.a+y.a, y.a);
}
HASH operator * (HASH x, HASH y) {
   return HASH(x.a*y.a, x.b*y.b);
}
bool operator == (HASH x, HASH y) {
   return x.a == y.a && x.b == y.b;
}
bool operator < (HASH x, HASH y) {
   return x.a == y.a ? x.b < y.b : x.a < y.a;
}
const HASH BAS(233, 157);
const int MAXN = 1e4+5;
const int MAXM = 1505;
int n;
char s[MAXM];
HASH h[MAXN];

HASH get_hash() {
   int len = strlen(s);
   HASH ret(0, 0);
   for(int i = 0; i < len; i++) ret = ret * BAS + HASH(s[i], s[i]);
   return ret;
}

int main() {
   //freopen("test.in", "r", stdin);
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) {
      scanf("%s", s);
      h[i] = get_hash();
   }
   std::sort(h+1, h+1+n);
   int tot = std::unique(h+1, h+1+n) - h - 1;
   printf("%d\n", tot);
   return 0;
}