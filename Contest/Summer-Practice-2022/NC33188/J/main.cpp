// https://ac.nowcoder.com/acm/contest/33188/J

#include<cstdio>
#include<deque>
using namespace std;
typedef pair<int, int> pr;
const int MAXN = 5e5 + 5;
const int INF = 1e9;

int n, c[MAXN][4], s1, s2, sj, t1, t2, tj;
int vis[MAXN][4], dis[MAXN][4];
deque<pr> de;
int getnum(int s, int t) {
   for(int j = 0; j < 4; j++)
      if(c[t][j] == s) return j;
   return -1;
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) {
      for(int j = 0; j < 4; j++) {
         scanf("%d", &c[i][j]);
      }
   }
   scanf("%d%d%d%d", &s1, &s2, &t1, &t2);
   sj = getnum(s1, s2);
   tj = getnum(t1, t2);
   for(int i = 1; i <= n; i++) for(int j = 0; j < 4; j++) dis[i][j] = INF;
   dis[s2][sj] = 0;
   de.push_front(pr(s2, sj));
   while(de.size()) {
      int u = de.front().first, uj = de.front().second; de.pop_front();
      if(vis[u][uj]) continue;
      vis[u][uj] = 1;
      if(u == t2 && uj == tj) break;
      for(int i = 0; i < 4; i++) {
         int dir = (uj + i) % 4, w = (i == 1) ? 0 : 1;
         int nx = c[u][dir];
         if(nx == 0) continue;
         int nxj = getnum(u, c[u][dir]);
         if(dis[nx][nxj] > dis[u][uj] + w) {
            dis[nx][nxj] = dis[u][uj] + w;
            if(w == 0) de.push_front(pr(nx, nxj));
            else {
               de.push_back(pr(nx, nxj));
            }
         }
      }
   }
   if(!vis[t2][tj]) printf("-1\n");
   else printf("%d\n", dis[t2][tj]);
   return 0;
}