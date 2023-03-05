/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 20:59:32
 * @Description: https://www.luogu.com.cn/problem/P3865
 * @Tag: 数据结构，st表，RMQ
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
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
int n, m, st[MAXN][17], lg2[MAXN];

int main() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++) st[i][0] = read();
   lg2[0] = -1; for(int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
   for(int k = 1; (1 << k) <= n; k++)
      for(int i = 1; i + (1 << k) - 1 <= n; i++)
         st[i][k] = max(st[i][k-1], st[i+(1 << (k-1))][k-1]);
   for(int i = 1; i <= m; i++) {
      int l = read(), r = read();
      int k = lg2[r-l+1];
      printf("%d\n", max(st[l][k], st[r - (1 << k) + 1][k]));
   }
   return 0;
}