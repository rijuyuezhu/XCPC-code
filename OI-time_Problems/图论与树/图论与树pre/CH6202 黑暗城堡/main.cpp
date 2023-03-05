//http://noi-test.zzstep.com/contest/0x60%E3%80%8C%E5%9B%BE%E8%AE%BA%E3%80%8D%E4%BE%8B%E9%A2%98/6202%20%E9%BB%91%E6%9A%97%E5%9F%8E%E5%A0%A1
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
const int MAXN = 1005;//point
const int MAXM = MAXN * MAXN / 2;
const int MO = 0x7fffffff;
int n, m;
struct Edge {
    int v, nxt;
    int w;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
typedef pair<int, int> pii;
int dist[MAXN], vis[MAXN];
priority_queue<pii, vector<pii>, greater<pii> > pq;

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0; pq.push(pii(0, 1));
    while(!pq.empty()) {
        int u = pq.top().second; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v, w = e[i].w;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(pii(dist[v], v));
            }
        }
    }
}

ll ans = 1;
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        addedge(u, v, w); addedge(v, u, w);
    }
    dijkstra();
    for(int u = 1; u <= n; u++) {
        int tot = 0;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v, w = e[i].w;
            if(dist[v] + w == dist[u])//v->u
                tot++;
        }
        if(tot) ans = ans * tot % MO;
    }
    printf("%lld\n", ans);
    return 0;
}