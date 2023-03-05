#include <algorithm>
#include <iostream>
using namespace std;

constexpr int MAXN = 2e4 + 5;
constexpr int MAXM = 2e5 + 5;
int n, m;
struct Edge {
    int v, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v)  {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}

int dfn[MAXN], low[MAXN], _dfn, cut[MAXN];

void tarjan(int u, int fa, int rt) {
    dfn[u] = low[u] = ++_dfn;
    int ch = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        if(!dfn[v]) {
            ch++;
            tarjan(v, u, rt);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                if(u != rt || ch >= 2)
                    cut[u] = 1;
            }
        } else
            low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i, 0, i);
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(cut[i])
            ++ans;
    cout << ans << '\n';
    for(int i = 1; i <= n; i++)
        if(cut[i])
            cout << i << ' ';
    cout << '\n';
    return 0;
}
