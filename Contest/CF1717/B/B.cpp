/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-04 10:15:39
 * @Description: https://codeforces.com/contest/1717/problem/B
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
constexpr int MAXN = 505;
int col[MAXN][MAXN];
int n, k, r, c;
void draw(int x, int y) {
   if(col[x][y])
      return ;
   col[x][y] = 1;
   draw(x == 1 ? n : x - 1, y == n ? 1 : y + 1);
}
void work() {
   n = read(), k = read(), r = read(), c = read();
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n; j++)
         col[i][j] = 0;
   for(int i = 1; i <= n; i++) {//draw (i, c)
      if((r - i) % k == 0) draw(i, c);
   }
   for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++)
         printf(col[i][j] ? "X" : ".");
      printf("\n");
   }
}
int main() {
   int t = read();
   while(t--)
      work();
   return 0;
}