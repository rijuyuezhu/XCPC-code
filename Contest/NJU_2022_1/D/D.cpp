/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-08 15:19:44
 * @Description: 
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
constexpr int MAXN = 1e5 + 5;
int n, q, p[MAXN], fa[MAXN][17], stk[MAXN], _stk, getrg[MAXN];
void work() {
   n = read(), q = read();
   for(int i = 1; i <= n; i++) p[i] = read();
   _stk = 0; p[n+1] = n+1; stk[++_stk] = n+1; getrg[n+1] = n+1;
   for(int i = 0; i <= 16; i++) fa[n+1][i] = n+1;
   for(int i = n; i >= 1; i--) {
      while(_stk >= 1 && p[stk[_stk]] < p[i]) --_stk;
      if(stk[_stk] == i+1) fa[i][0] = fa[i+1][0], getrg[i] = getrg[i+1];
      else fa[i][0] = stk[_stk], getrg[i] = i;
      stk[++_stk] = i;
   }
   for(int i = 1; i <= 16; i++)
      for(int j = 1; j <= n; j++)
         fa[j][i] = fa[fa[j][i-1]][i-1];
   for(int t = 1; t <= q; t++) {
      int l = read(), r = read();
      int now = l, ans = 0;
      for(int k = 16; k >= 0; k--) 
         if(fa[now][k] <= r)
            ans += (1 << k), now = fa[now][k];
      if(getrg[now] < r) ++ans;
      printf("%d\n", ans);
   }
}
int main() { 
   int T = read();
   while(T--) work();
   return 0;
}