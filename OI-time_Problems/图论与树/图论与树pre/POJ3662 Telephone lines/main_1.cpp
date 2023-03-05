//http://poj.org/problem?id=3662
//分层图
//还可以二分做
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e3 + 5;
const int MAXM = 1e4 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
//point[n][k]代表从n号点出发，已经使用了k个免费的点
int n, m, k;
struct Edge {
    int v, nxt;
    ll w;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt].v  = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
ll dist[MAXN][MAXN];
bool vist[MAXN][MAXN];
typedef pair<int, int> pii;
typedef pair<ll, pii> pli;
priority_queue<pli, vector<pli>, greater<pli> > pq;

int main() {
    n = read(), m = read(), k = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(); ll w = read();
        addedge(u, v, w);
        addedge(v, u, w);
    }   
    memset(dist, 0x3f, sizeof dist);
    dist[1][0] = 0; pq.push(pli(0, pii(1, 0)));
    while(!pq.empty()) {
        pii now = pq.top().second; pq.pop();
        int u = now.first, ku = now.second;
        if(vist[u][ku]) continue;
        vist[u][ku] = 1;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v; ll w = e[i].w;
            if(!vist[v][ku] && dist[v][ku] > max(dist[u][ku], w)) {//不使用免费
                dist[v][ku] = max(dist[u][ku], w);
                pq.push(pli(dist[v][ku], pii(v, ku)));
            }
            if(ku < k && !vist[v][ku+1] && dist[v][ku+1] > dist[u][ku]) {//使用免费
                dist[v][ku+1] = dist[u][ku];
                pq.push(pli(dist[v][ku+1], pii(v, ku+1)));
            }
        }
    }
    ll ans = INF;
    for(int i = 0; i <= k; i++) ans = min(ans, dist[n][i]);
    if(ans == INF) printf("-1\n");
    else printf("%lld\n", ans);
    return 0;
}