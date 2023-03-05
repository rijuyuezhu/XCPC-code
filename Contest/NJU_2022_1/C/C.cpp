/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-08 14:51:23
 * @Description: 
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
using ll = long long;
using db = double;
using pr = pair<int, int>;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
constexpr int MAXN = 305;
int n, match[MAXN], vis[MAXN];
vector<int> G[MAXN];
vector<pr> col[MAXN * MAXN];
int mxcol;
vector<pr> ans;
bool dfs(int u) {
   for(auto v : G[u]) {
      if(vis[v]) continue;
      vis[v] = 1;
      if(!match[v] || dfs(match[v])) {
         match[v] = u;
         return 1;
      }
   }
   return 0;
}
void work() {
   n = read();
   for(int i = 1; i <= n * n; i++) col[i].clear();
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n; j++) {
         int c = read();
         col[c].push_back(pr(i, j));
      }
   ans.clear(); mxcol = 0;
   for(int i = 1; i <= n * n; i++) {
      if(col[i].size()) {
         for(int j = 1; j <= n; j++) G[j].clear();
         for(auto k : col[i]) {
            G[k.first].push_back(k.second);
         }
         for(int j = 1; j <= n; j++) match[j] = 0;
         for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) vis[k] = 0;
         }
         for(auto k : col[i]) {
            if(match[k.second] != k.first) ans.push_back(k);
         }
      }
   }
   printf
   for(auto k : ans)
      printf("%d %d  ")
}
int main() {
   int T = read();
   while(T--) work();
   return 0;
}