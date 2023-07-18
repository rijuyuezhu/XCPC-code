// https://codeforces.com/contest/1703/problem/B

#include<cstdio>

int cnt[100], n, ans;
char s[100];
void work() {
   for(int i = 0; i < 26; i++) cnt[i] = 0;
   ans = 0;
   scanf("%d%s", &n, s);
   for(int i = 0; i < n; i++) {
      cnt[s[i]-'A']++;
   }
   for(int i = 0; i < 26; i++) if(cnt[i]) ans += cnt[i] + 1;
   printf("%d\n", ans);
}
int main() {
   int t; scanf("%d", &t);
   for(int i = 1; i <= t; i++) work();
   return 0;
}