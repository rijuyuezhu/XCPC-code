#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;
const int MAXK = 105;
const ll INF = 1e18;
int head[MAXN], cnt, n, k, deg[MAXN], szlf[MAXN], islf[MAXN], rt;
ll f[MAXN][MAXK], g[MAXN][MAXK], h[MAXK];
struct Edge {int v, nxt, w;}e[MAXN << 1];
void addedge(int u, int v, int w) {
    e[++cnt] = {v, head[u], w}, head[u] = cnt;
}

void dfs(int u, int fa) {
    if(islf[u]) szlf[u] = 1;
    else szlf[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == fa) continue;
        dfs(v, u); szlf[u] += szlf[v];
    }
    for(int t = 0, for_up = min(k, szlf[u]); t <= for_up; t++) {
        f[u][t] = g[u][t] = INF;
    }
    if(islf[u]) {
        f[u][0] = 0, f[u][1] = 0;
        return ;
    }
    f[u][0] = 0;
    int nowszlf = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == fa) continue;
        for(int t = 0; t <= nowszlf; t++)
            h[t] = f[u][t], f[u][t] = INF;
        for(int t = 0, for_up = min(szlf[v], k); t <= for_up; t++) {
            if(f[v][t] == INF) continue;
            g[v][t] = f[v][t] + 1ll * t * (k - t) * e[i].w;
            for(int q = 0, for_up = min(nowszlf, k - t); q <= for_up; q++)
                if(h[q] != INF)
                    f[u][t+q] = min(f[u][t+q], g[v][t] + h[q]);
        }
        nowszlf += szlf[v];
    }
}

void work(int te) {
    scanf("%d%d", &n, &k);

    for(int i = 1; i <= n; i++)
        head[i] = deg[i] = szlf[i] = islf[i] = 0;
    cnt = rt = 0;

    for(int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
        deg[u]++; deg[v]++;
    }
    if(n == 2) {
        if(k == 1) printf("Case #%d: 0\n", te);
        else printf("Case #%d: %d\n", te, e[1].w);
        return;
    }
    for(int i = 1; i <= n; i++)
        if(deg[i] == 1)
            islf[i] = 1;
        else if(!rt)
            rt = i;
    dfs(rt, 0);
    printf("Case #%d: %lld\n", te, f[rt][k]);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) work(i);
    return 0;
}