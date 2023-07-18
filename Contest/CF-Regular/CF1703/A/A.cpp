// https://codeforces.com/contest/1703/problem/0

#include<cstdio>
char s[5];
void work() {
   scanf("%s", s);
   if((s[0] == 'y' || s[0] == 'Y')
      && (s[1] == 'e' || s[1] == 'E')
      && (s[2] == 's' || s[2] == 'S'))
      printf("YES\n");
   else printf("NO\n");
}
int main() {
   //freopen("text.in", "r", stdin);
   int t; scanf("%d", &t);
   for(int i = 1; i <= t; i++) work();
   return 0;
}