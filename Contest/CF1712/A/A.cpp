/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-13 22:36:26
 * @Description: https://codeforces.com/contest/1712/problem/0
 * @Tag: 
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
const int MAXN = 105;
int n, k, p[MAXN], id[MAXN];
bool cmp(int a, int b) {
   if(p[a] == p[b]) return a < b;
   return p[a] < p[b];
}
void work() {
   n = read(), k = read();
   for(int i = 1; i <= n; i++) p[i] = read(), id[i] = i;
   sort(id + 1, id + 1 + n, cmp);
   int ans = 0;
   for(int i = 1; i <= k; i++) {
      if(id[i] > k) ans++;
   }
   printf("%d\n", ans);
}
int main() {
   int t = read();
   while(t--) work();
   return 0;
}
