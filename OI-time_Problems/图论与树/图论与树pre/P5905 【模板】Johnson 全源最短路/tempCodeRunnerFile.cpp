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
const int MAXN = 3e3 + 5;
const int MAXM = 6e3 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m;
struct Edge {
    int v, nxt;
    ll w;
}e[2 * MAXM];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}
queue<int> que;
int inq[MAXN], tot[MAXN];
ll h[MAXN];
bool spfa() {
    que.push(0); inq[0] = 1;
    memset(h, 0x3f, sizeof h);
    h[0] = 0; tot[0] = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop(); inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(h[v] > h[u] + e[i].w) {
                h[v] = h[u] + e[i].w;
                tot[v] = tot[u] + 1;
                if(tot[v] >= n + 1) return 0;
                if(!inq[v]) que.push(v), inq[v] = 1;
            }
        }
    }
    return 1;
}
struct Node {
    int u; ll d;
    Node(int u = 0, ll d = 0ll) : u(u), d(d) {}
    bool operator < (const Node& B)const {
        return d > B.d;
    }
};
priority_queue<Node> pq;
ll dist[MAXN];
bool vis[MAXN];
void dij(int st) {
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0x00, sizeof vis);
    while(!pq.empty()) pq.pop();
    dist[st] = 0; pq.push(Node(st, 0));
    while(!pq.empty()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(dist[v] > dist[u] + e[i].w) {
                dist[v] = dist[u] + e[i].w;
                pq.push(Node(v, dist[v]));
            }
        }
    }
}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        addedge(u, v, w);
    }
    for(int i = 1; i <= n; i++) addedge(0, i, 0);
    if(!spfa()) {
        printf("-1");
        return 0;
    }
    for(int u = 1; u <= n; u++)
        for(int i = head[u]; i; i = e[i].nxt) 
            e[i].w += h[u] - h[e[i].v];
    for(int i = 1; i <= n; i++) {
        dij(i);
        ll ans = 0;
        for(int j = 1; j <= n; j++)
            if(dist[j] == INF) ans += j * 1e9;
            else ans += j * (dist[j] + h[j] - h[i]);
        printf("%lld\n", ans);
    }
    return 0;
}
