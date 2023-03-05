/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:27:15
 * @Description: https://www.luogu.com.cn/problem/P3367
 * @Tag: 并查集
*/



#include<cstdio>
const int MAXN = 1e4 + 5;
const int MAXM = 2e5 + 5;
int N, M, upto[MAXN];
int getup(int x) {
   return x == upto[x] ? x : upto[x] = getup(upto[x]);
}
int main() {
   scanf("%d%d", &N, &M);
   for(int i = 1; i <= N; i++) upto[i] = i;
   for(int i = 1; i <= M; i++) {
      int opt, x, y;
      scanf("%d%d%d", &opt, &x, &y);
      if(opt == 1) {
         x = getup(x); y = getup(y);
         if(x == y) continue;
         upto[x] = y;
      } else {
         x = getup(x); y = getup(y);
         printf(x == y ? "Y\n" : "N\n");
      }
   }
   return 0;
}