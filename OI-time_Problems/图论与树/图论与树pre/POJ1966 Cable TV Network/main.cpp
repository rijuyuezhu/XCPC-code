// http://poj.org/problem?id=1966
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 105;
const int MAXM = 100005;
const int INF = 5e8;
int n, m;
int G[MAXN][MAXN];
int s, t;
struct Edge {
    int v, w, nxt;
}e[MAXM];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}
int d[MAXN];
queue<int> q;
bool bfs() {
    memset(d, 0x00, sizeof d);
    while(!q.empty()) q.pop();
    q.push(s); d[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(!d[v] && e[i].w) {
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int flow) {
    if(u == t) return flow;
    int rest = flow;
    for(int i = head[u]; i && rest; i = e[i].nxt) {
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].w) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) d[v] = 0;
            rest -= k;
            e[i].w -= k;
            e[i^1].w += k;
        }
    }
    return flow - rest;
}
int dinic() {
    int flow, ans = 0;
    while(bfs())
        while(flow = dfs(s, INF)) ans += flow;
    return ans; 
}
void solve() {
    memset(G, 0x00, sizeof G);
    int ans = INF;
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        G[u][v] = G[v][u] = 1;
    }
    for(s = 0; s < n; s++)
        for(t = 0; t < n; t++) if(s != t) {
            memset(head, 0x00, sizeof head); cnt = 1;
            for(int i = 0; i < n; i++)
             if(i != s && i != t)
                addedge(i, i + n, 1), addedge(i + n, i, 0);
             else
                addedge(i, i + n, INF), addedge(i + n, i, 0);
                //点边转化！！！
            for(int i = 0; i < n; i++)
             for(int j = 0; j < n; j++)
              if(G[i][j])
                addedge(i + n, j, INF) , addedge(j, i + n, 0);
             ans = min(ans, dinic());
        }
    if(n <= 1 || ans == INF) ans = n;
    printf("%d\n", ans);
}
int main() {
    while(scanf("%d%d", &n, &m) != EOF) solve();
    return 0;
}