// https://codeforces.com/contest/1699/problem/A

#include<cstdio>

int main() {
   int t;
   scanf("%d", &t);
   for(int i = 1; i <= t; i++) {
      int n; scanf("%d", &n);
      if(n & 1) printf("-1\n");
      else {
         printf("%d %d %d\n", 0, n/2, n/2);
      }
   }
   return 0;
}


