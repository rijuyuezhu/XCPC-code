// https://codeforces.com/contest/1699/problem/B

#include<cstdio>

int n, m;
void work() {
   scanf("%d%d", &n, &m);
   for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
         int a = (i & 1) ^ (j & 1);
         if((i % 4 >= 2) ^ (j % 4 >= 2)) a ^= 1;
         printf("%d ", a);
      }
      printf("\n");
   }
}
int main() {

   int t;
   scanf("%d", &t);
   for(int i = 1; i <= t; i++) work();
   return 0;
}