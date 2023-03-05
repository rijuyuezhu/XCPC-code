/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-15 18:52:59
 * @Description: https://codeforces.com/contest/1712/problem/D
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
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
const int V = 1e9;
int n, k, a[MAXN], id[MAXN];
bool cmp(int x, int y) {return a[x] < a[y];}
void work() {
   n = read(), k = read();
   for(int i = 1; i <= n; i++)
      a[i] = read(), id[i] = i;
   if(k == n) {
      printf("%d\n", V);
      return ;
   }
   sort(id + 1, id + 1 + n, cmp);
   for(int i = 1; i < k; i++)
      a[id[i]] = V;

   /*-----type 2------*/
   int ans1 = 0;
   for(int i = 1; i <= n; i++)
      ans1 = max(a[i], ans1);
   ans1 = min(ans1, 2 * a[id[k]]);

   /*-----type 1------*/
   int ans2 = 0, v = a[id[k]];
   for(int i = 1; i < n; i++) ans2 = max(ans2, min(a[i], a[i+1]));
   for(int i = 1; i <= n; i++)
      if(a[i] == v) {
         if(i > 1) ans2 = max(ans2, a[i-1]);
         if(i < n) ans2 = max(ans2, a[i+1]);
      }
   ans2 = min(ans2, 2 * a[id[k+1]]);
   printf("%d\n", max(ans1, ans2));
}
int main() {
   int t = read();
   while(t--) work();
   return 0;
}