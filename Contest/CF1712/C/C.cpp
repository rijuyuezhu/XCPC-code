/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-13 22:41:48
 * @Description: https://codeforces.com/contest/1712/problem/B
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 1e5 + 5;
int n, a[MAXN], des[MAXN], ans, fl, cnt[MAXN], bef[MAXN];
void work() {
   n = read();
   ans = 0; fl = 0;
   for(int i = 1; i <= n; i++) bef[i] = 0, cnt[i] = 0, des[i] = 0;
   for(int i = 1; i <= n; i++) {
      a[i] = read();
      if(!bef[a[i]]) bef[a[i]] = i;
      cnt[a[i]]++;
   }
   for(int i = n; i >= 1; i--) {
      if(!fl) {
         if(i < n && a[i] > a[i+1]) fl = 1;
         if(bef[a[i]] && i - bef[a[i]] + 1 > cnt[a[i]]) fl = 1;
      }
      if(fl) {
         if(!des[a[i]]) des[a[i]] = 1, ans++;
      }
   }
   printf("%d\n", ans);
}

int main() {
   int t = read();
   while(t--) work();
   return 0;
}