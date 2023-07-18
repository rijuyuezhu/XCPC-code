// https://codeforces.com/contest/1703/problem/C

#include<cstdio>

const int MAXN = 105;
const int MAXBI = 15;
int n, a[MAXN];
char s[MAXBI];
void work() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   for(int i = 1; i <= n; i++) {
      int c; scanf("%d", &c);
      scanf("%s", s);
      for(int j = c-1; j >= 0; j--)
         if(s[j] == 'U') a[i]--;
         else a[i]++;
      a[i] = ((a[i] % 10) + 10) % 10;
      printf("%d ", a[i]);
   }
   printf("\n");
}
int main() {
   //freopen("C.in", "r", stdin);
   int t; scanf("%d", &t);
   for(int i = 1; i <= t; i++) work(); 
   return 0;
}