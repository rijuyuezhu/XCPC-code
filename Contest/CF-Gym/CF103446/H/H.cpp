#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 2e5 + 5;
constexpr int MAXM = 2e5 + 5;
constexpr int INF = 0x3f3f3f3f;
struct DSU {
    int fa[MAXN];
    void init(int n) {
        for(int i = 1; i <= n; i++)
            fa[i] = i;
    }
    int getfa(int u) {
        return fa[u] == u ? u : getfa(fa[u]);
    }
};
struct Ed {
    int u, v, w;
    bool operator < (const Ed &B)const {
        return w < B.w;
    }
}ed[MAXM];
struct Edge {
    int v, nxt;
}e[MAXN];
int n, m, q, a[MAXN], val[MAXN], num, cnt, head[MAXN], rt;
void addedge(int u, int v) {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}

void Kruskal() {
    static DSU dsu;
    dsu.init(2 * n - 1);
    sort(ed + 1, ed + 1 + m);
    num = n;
    for(int i = 1; i <= m; i++) {
        int fu = dsu.getfa(ed[i].u), fv = dsu.getfa(ed[i].v);
        if(fu == fv)
            continue;
        ++num;
        val[num] = ed[i].w;
        addedge(num, fu);
        addedge(num, fv);
        dsu.fa[fu] = dsu.fa[fv] = num;
    }
    rt = num;
}

int fa[17][MAXN], dist[17][MAXN]+


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= m; i++) {
        cin >> ed[i].u >> ed[i].v >> ed[i].w;
    }
    Kruskal();
    return 0;
}
