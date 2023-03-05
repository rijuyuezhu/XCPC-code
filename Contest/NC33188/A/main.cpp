// https://ac.nowcoder.com/acm/contest/33188/A

#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 5;
int n, k;
int x[MAXN], a[MAXN];

struct Edge{int v, nxt;}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
   e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;
}

int siz[MAXN], ans[MAXN], ansa[MAXN];
bool isch[MAXN];
void dfs(int u) {
   int sz1 = 0, sz2 = 0;
   for(int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v; dfs(v);
      siz[u] += siz[v];
      if(siz[v] >= 2) sz2++;
      else if(siz[v] == 1) sz1++;
   }
   if(isch[u]) siz[u]++;
   if(siz[u] == k-1) {
      if(sz2 + sz1 >= 2 || isch[u]) ans[u] = 1;
      else ans[u] = 0;
   } else if(siz[u] == k) {
      if(isch[u]) {
         if(sz2 + sz1 >= 2) ans[u] = k;
         else if(sz2 + sz1 == 1) ans[u] = k-1;
         else ans[u] = 0;
      } else {
         if(sz2 >= 2) ans[u] = k;
         else if(sz2 == 1) {
            if(sz1 >= 2) ans[u] = k;
            else if(sz1 == 1) {
               ans[u] = k-1;
            } else {
               ans[u] = 0;
            }
         } else {
            if(sz1 >= 3) ans[u] = k;
            else ans[u] = 0;
         }
      }
   }
}

struct Item {
   int v, ty, num;
}t[MAXN];
int _t;
bool operator < (Item a, Item b) {
   return a.v == b.v ? a.ty < b.ty : a.v < b.v;
}
void work(int ty) {
   for(int i = 1; i <= n; i++) {
      siz[i] = ans[i] = isch[i] = 0;
   }
   for(int i = 1; i <= k; i++) isch[x[i]] = 1;
   dfs(1);
   for(int i = 1; i <= n; i++) if(ans[i]) {
      t[++_t] = (Item){a[i], ty, ans[i]};
   }
}
int main() {
   freopen("main.in", "r", stdin);
   freopen("main.out", "w", stdout);
   scanf("%d%d", &n, &k);
   for(int i = 1; i <= k; i++) scanf("%d", &x[i]);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   for(int i = 2; i <= n; i++) {
      int p; scanf("%d", &p);
      addedge(p, i);
   }
   work(1);
   cnt = 0; for(int i = 1; i <= n; i++) head[i] = 0;
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   for(int i = 2; i <= n; i++) {
      int p; scanf("%d", &p);
      addedge(p, i);
   }
   work(2);
   sort(t + 1, t + 1 + _t);
   ll ans = 0, sum = 0;
   for(int i = 1; i <= _t; i++) {
      if(t[i].ty == 1) ans += sum * t[i].num;
      else sum += t[i].num;
   }
   printf("%lld\n", ans);
   return 0;
}