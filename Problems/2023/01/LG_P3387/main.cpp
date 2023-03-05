#include <iostream>
#include <iostream>
using namespace std;

constexpr int MAXN = 1e4 + 5;
constexpr int MAXM = 1e5 + 5;

int n, m, a[MAXN];
struct Graph {
    struct Edge {
        int v, nxt;
    }e[MAXM];
    int head[MAXN], cnt;
    void addedge(int u, int v) {
        e[++cnt] = {v, head[u]};
        head[u] = cnt;
    }
}G1, G2;

int dfn[MAXN], low[MAXN], _dfn, stk[MAXN], top, ins[MAXN], scc[MAXN], _scc, scc_sum[MAXN], deg[MAXN], que[MAXN], hd, tl, f[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++_dfn;
    stk[++top] = u;
    ins[u] = 1;
    for(int i = G1.head[u]; i; i = G1.e[i].nxt) {
        int v = G1.e[i].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        ++_scc;
        int t;
        do {
            t = stk[top--];
            ins[t] = 0;
            scc[t] = _scc;
            scc_sum[_scc] += a[t];
        }while(t != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G1.addedge(u, v);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i);
    for(int u = 1; u <= n; u++)
        for(int i = G1.head[u]; i; i = G1.e[i].nxt) {
            int v = G1.e[i].v;
            if(scc[u] == scc[v]) continue;
            G2.addedge(scc[u], scc[v]);
            deg[scc[v]]++;
        }
    hd = 1; tl = 0;
    for(int i = 1; i <= _scc; i++)
        if(deg[i] == 0) {
            que[++tl] = i;
            f[i] = scc_sum[i];
        }
    while(hd <= tl) {
        int u = que[hd++];
        for(int i = G2.head[u]; i; i = G2.e[i].nxt) {
            int v = G2.e[i].v;
            f[v] = max(f[v], f[u] + scc_sum[v]);
            if(--deg[v] == 0)
                que[++tl] = v;
        }
    }
    int ans = 0;
    for(int i = 1; i <= _scc; i++)
        ans = max(ans, f[i]);
    cout << ans << '\n';
    return 0;
}
