#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
using pr = pair<ll, int>;
const int MAXN = 2e6 + 5;
const int MAXM = 4e6 + 5;
const ll INF = 0x3fffffffffffffff;
int n, m;
priority_queue<pr, vector<pr>, greater<pr> > pq;
struct Edge {
    int v, nxt;
    ll w;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt] = {v, head[u], w}; head[u] = cnt;
}
ll dist[MAXN];
int vis[MAXN];

void dijkstra(int s) {
    for(int i = 0; i <= n; i++)
        dist[i] = INF, vis[i] = 0;
    dist[s] = 0; pq.push(pr(0, s));
    while(pq.size()) {
        int u = pq.top().second; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v; ll w = e[i].w;
            if(vis[v]) continue;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(pr(dist[v], v));
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int u, v; ll w;
        scanf("%d%d%lld", &u, &v, &w);
        addedge(u, v, 2 * w);
        addedge(v, u, 2 * w);
    }
    for(int i = 1; i <= n; i++) {
        ll t;
        scanf("%lld", &t);
        addedge(0, i, t);
    }
    dijkstra(0);
    for(int i = 1; i <= n; i++)
        printf("%lld ", dist[i]);
    printf("\n");
    return 0;
}