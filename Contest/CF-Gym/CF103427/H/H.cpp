#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

constexpr int MAXN = 1e5 + 5;
constexpr int MAXM = 4e5 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, m;
struct Graph {
    struct Edge {
        int v, w, nxt;
    }e[MAXM];
    int head[MAXN], cnt = 1;
    void addedge(int u, int v, int w) {
        e[++cnt] = {v, w, head[u]};
        head[u] = cnt;
    }
}G, S;

int dfn[MAXN], low[MAXN], _dfn, cut[MAXM];
int vis[MAXN], bcc[MAXN], _bcc, bcc_val[MAXN], minw, siz[MAXN];
ll totw;

void tarjan(int u, int toe) {
    dfn[u] = low[u] = ++_dfn;
    for(int i = G.head[u]; i; i = G.e[i].nxt) {
        if((i ^ 1) == toe)
            continue;
        int v = G.e[i].v;
        if(!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])
                cut[i] = cut[i ^ 1] = 1;
        } else
            low[u] = min(low[u], dfn[v]);
    }
}

void dfs(int u) {
    vis[u] = 1;
    bcc[u] = _bcc;
    for(int i = G.head[u]; i; i = G.e[i].nxt) {
        if(cut[i])
            continue;
        int v = G.e[i].v;
        if(vis[v])
            continue;
        dfs(v);
    }
}


void dfs2(int u, int fa) {
    siz[u] = bcc_val[u];
    for(int i = S.head[u]; i; i = S.e[i].nxt) {
        int v = S.e[i].v, w = S.e[i].w;
        if(v == fa) continue;
        dfs2(v, u);
        if(siz[v] % 2 == 0)
            minw = min(minw, w);
        siz[u] += 1 + siz[v];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.addedge(u, v, w);
        G.addedge(v, u, w);
        totw += w;
    }
    if(m % 2 == 0) {
        cout << totw << '\n';
        return 0;
    }
    minw = INF;
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) //connected, so not necessary.
            tarjan(i, 0);
    for(int i = 1; i <= n; i++)
        if(!vis[i]) {
            ++_bcc;
            dfs(i);
        }
    for(int u = 1; u <= n; u++)
        for(int i = G.head[u]; i; i = G.e[i].nxt) {
            if(i & 1)
                continue;
            int v = G.e[i].v, w = G.e[i].w;
            if(bcc[u] == bcc[v]) {
                ++bcc_val[bcc[u]];
                minw = min(minw, w);
            } else {
                S.addedge(bcc[u], bcc[v], w);
                S.addedge(bcc[v], bcc[u], w);
            }
        }
    dfs2(1, 0);
    cout << totw - minw << '\n';
    return 0;
}

