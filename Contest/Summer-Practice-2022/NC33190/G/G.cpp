/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-01 12:36:11
 * @Description: https://ac.nowcoder.com/acm/contest/33190/G
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXL = 1e6 + 5;
char s[MAXL], t[MAXL];
/*
1 : t[i] = $
2, 4, 6, ... 2n+2: t[i] = #
3, 5, 7, ... 2n+1 : t[2n+1] = s[n]
*/
int r[MAXL], n, nt, d[MAXL];
int main() {
   n = read(); scanf("%s", s+1);
   t[1] = '$'; t[2] = '#';
   for(int i = 1; i <= n; i++)
      t[2 * i + 1] = s[i], t[2 * i + 2] = '#';
   nt = n * 2 + 2;
   int c = 0;
   for(int i = 1; i <= nt; i++) {
      if(i < c + r[c]) r[i] = min(c + r[c] - i, r[2 * c - i]);
      while(i + r[i] <= nt && t[i + r[i]] == t[i - r[i]]) r[i]++;
      if(i + r[i] > c + r[c]) c = i;
   }
   for(int i = 1; i <= nt; i++) {
      d[i]++;
      d[i + r[i]]--;
   }
   for(int i = 1; i <= nt; i++) d[i] += d[i-1];
   int ans = 0;
   for(int i = 1; i <= nt; i++)
      if(t[i] == 'k') ans += d[i];
   printf("%d ", ans);
   ans = 0;
   for(int i = 1; i <= nt; i++)
      if(t[i] == 'f') ans += d[i];
   printf("%d ", ans);
   ans = 0;
   for(int i = 1; i <= nt; i++)
      if(t[i] == 'c') ans += d[i];
   printf("%d ", ans);
   return 0;
}