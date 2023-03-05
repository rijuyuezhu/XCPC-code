/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:25:54
 * @Description: https://www.luogu.com.cn/problem/P1886
 * @Tag: 单调队列
*/



#include<cstdio>

const int MAXN = 1e6+5;

int n, k, a[MAXN], que[MAXN], hd, tl;

int main() {
   scanf("%d%d", &n, &k);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   hd = 1; tl = 0;
   for(int i = 1; i <= n; i++) {
      while(hd <= tl && a[i] < a[que[tl]]) tl--;
      que[++tl] = i;
      while(hd <= tl && que[hd] < i-k+1) hd++;
      if(i-k+1 >= 1) printf("%d ", a[que[hd]]);
   }
   printf("\n");
   hd = 1; tl = 0;
   for(int i = 1; i <= n; i++) {
      while(hd <= tl && a[i] > a[que[tl]]) tl--;
      que[++tl] = i;
      while(hd <= tl && que[hd] < i-k+1) hd++;
      if(i-k+1 >= 1) printf("%d ", a[que[hd]]);
   }
   printf("\n");
}