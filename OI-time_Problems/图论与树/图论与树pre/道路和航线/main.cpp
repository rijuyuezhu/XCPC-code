//http://ybt.ssoier.cn:8088/problem_show.php?pid=1503
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
const int MAXT = 2.5e4 + 5;
const int MAXR = 5e4 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int t, r, p, s;
struct Edge {
    int v, nxt;
    ll w;
}e[MAXR * 3];
int head[MAXT], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int c[MAXT], col;
void dfs(int u) {
    c[u] = col;
    for(int i = head[u]; i; i = e[i].nxt) {
        if(c[e[i].v]) continue;
        dfs(e[i].v);
    }
}
int deg[MAXT];
queue<int> topu;
typedef pair<ll, int> pli;
priority_queue<pli, vector<pli>, greater<pli> > pq;
ll dist[MAXT];
int vis[MAXT];
int main() {
    t = read(), r = read(), p = read(), s = read();
    for(int i = 1; i <= r; i++) {
        int u = read(), v = read();
        ll w = read();
        addedge(u, v, w);
        addedge(v, u, w);
    }
    for(int i = 1; i <= t; i++)
        if(!c[i]) {
            col++;
            dfs(i);
        }
    for(int i = 1; i <= p; i++) {
        int u = read(), v = read();
        ll w = read();
        addedge(u, v, w);
        deg[c[v]]++;
    }

    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    topu.push(c[s]);
    for(int i = 1; i <= col; i++)
        if(!deg[i])
            topu.push(i);
    
    while(!topu.empty()) {
        int now = topu.front(); topu.pop();
        for(int i = 1; i <= t; i++)
            if(c[i] == now)
                pq.push(pli(dist[i], i));
        while(!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if(vis[u]) continue;
            vis[u] = 1;
            for(int i = head[u]; i; i = e[i].nxt) {
                int v = e[i].v;
                if(dist[v] > dist[u] + e[i].w) {
                    dist[v] = dist[u] + e[i].w;
                    if(c[u] == c[v]) pq.push(pli(dist[v], v));
                }
                if(c[u] != c[v])
                    if(--deg[c[v]] == 0) topu.push(c[v]);
            }
        }
    }
    for(int i = 1; i <= t; i++)
        if(dist[i] > 0x3f3f3f3f) printf("NO PATH\n");//由于负权的存在，绝对不能dist[i]==INF
        else printf("%lld\n", dist[i]);
    return 0;
}