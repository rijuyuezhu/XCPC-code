/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-14 15:15:22
 * @Description: https://www.luogu.com.cn/problem/P4306  
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<bitset>
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
int read01() {
   char ch = getchar();
   for(; ch != '0' && ch != '1'; ch = getchar());
   return ch - '0';
}
const int MAXN = 2005;
int n;
bitset<MAXN> G[MAXN];
int main() {
   n = read();
   for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++)
         G[i][j] = read01();
      G[i][i] = 1;
   }
   for(int k = 1; k <= n; k++)
      for(int i = 1; i <= n; i++)
         if(G[i][k])
            G[i] |= G[k];
   int ans = 0;
   for(int i = 1; i <= n; i++) ans += G[i].count();
   printf("%d\n", ans);
   return 0;
}