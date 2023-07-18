#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
using db = double;
constexpr int MAXN = 1005;
constexpr int P = 998244353;
int n, m, a[MAXN];
struct Edge {int v, nxt;}e[MAXN];
int head[MAXN], cnt, deg[MAXN], topu[MAXN], _topu, ed, ans, time_zero, end_time;
int b[MAXN], d[MAXN], dp[MAXN];
queue<int> que;
void addedge(int u, int v) {
   e[++cnt] = {v, head[u]}; head[u] = cnt;
}

void work() {
   cin >> n >> m;
   for(int i = 1; i <= n; i++) {
      head[i] = deg[i] = 0;
   }
   cnt = _topu = time_zero = ans = end_time = 0;
   que = queue<int>();
   for(int i = 1; i <= n; i++)   
      cin >> a[i];
   for(int i = 1; i <= m; i++) {
      int u, v; cin >> u >> v;
      addedge(u, v);
      deg[v]++;
   }
   for(int i = 1; i <= n; i++)
      if(!deg[i])
         que.push(i);
   while(que.size()) {
      int u = que.front(); que.pop();
      topu[++_topu] = u;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         if(!--deg[v]) que.push(v);
      }
   }
   ed = topu[n];
   for(int i = 1; i <= n; i++) b[i] = a[i];
   end_time = 0;
   for(int i = 1; i <= n; i++) 
      if(b[i] > 0)
         end_time = 1;
   for(int t = 1; t <= n; t++) {//stimulate n times
      for(int i = 1; i <= n; i++)
         d[i] = 0;
      for(int i = 1; i <= n; i++)
         if(b[i] > 0) {
            d[i]--;
            for(int j = head[i]; j; j = e[j].nxt) {
               int v = e[j].v;
               d[v]++;
            }
         }
      for(int i = 1; i <= n; i++) b[i] += d[i];
      if(b[ed] == 0) time_zero++;
      else end_time = t + 1;
   }
   dp[ed] = 1;
   bool fl = 0;
   for(int k = n-1; k >= 1; k--) {
      int u = topu[k];
      dp[u] = 0;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         dp[u] = (dp[v] + dp[u]) % P;
      }
   }
   for(int i = 1; i <= n; i++) {
      ll tmp = ans + 1ll * a[i] * dp[i];
      if(tmp >= P) fl = 1;
      ans = tmp % P;
   }
   if(ans + time_zero > n + 1) fl = 1;
   if(fl) cout << 'A' << ' ' << (ans + time_zero) % P  << endl;
   else cout << 'B' << ' ' << end_time << endl;
}
int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cout.tie(nullptr);
   int t;
   cin >> t;
   while(t--)
      work();
   return 0;
}