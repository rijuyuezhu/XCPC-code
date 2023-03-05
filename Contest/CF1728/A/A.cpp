/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-11 12:45:57
 * @Description: 
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
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
using pr = pair<int, int>;
constexpr int MAXN = 25;
int n, cnt[MAXN];
queue<pr> q;
void work() {
   n = read();
   for(int i = 1; i <= n; i++) cnt[i] = read();
   q = queue<pr>();
   for(int i = 1; i <= n; i++) q.push(pr(i, cnt[i]));
   while(q.size() >= 2) {
      auto u = q.front(); q.pop();
      auto v = q.front(); q.pop();
      if(u.second == v.second) continue;
      if(u.second < v.second) swap(u, v);
      q.push(pr(u.first, u.second - v.second));
   }
   printf("%d\n", q.front().first);
}
int main() {
   int t = read();
   while(t--) work();   
   return 0;
}