/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-04 10:33:45
 * @Description: https://codeforces.com/contest/1717/problem/C
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
constexpr int MAXN = 2e5 + 5;
int n, a[MAXN], b[MAXN];
bool check() {
   n = read();
   for(int i = 1; i <= n; i++) a[i] = read();
   for(int i = 1; i <= n; i++) b[i] = read();
   
   for(int i = 1; i <= n; i++)
      if(a[i] > b[i] || (a[i] != b[i] && b[i] > b[i == n ? 1 : i + 1] + 1)) 
         return 0;
   return 1;
}
int main() {
   int t = read();
   while(t--)
      if(check()) 
         printf("YES\n");
      else
         printf("NO\n");
   return 0;
}