#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAXN = 5e5 + 5;
constexpr int MAXM = 1e6 + 5;
int n, m, a[MAXN];
struct Edge {
    int v, nxt;
}e[MAXM];
int head[MAXN], cnt = 1;
void addedge(int u, int v) {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}

int dfn[MAXN], low[MAXN], _dfn, cut[MAXM], ret, vis[MAXN];
vector<int> ans;


void tarjan(int u, int toe) {
    dfn[u] = low[u] = ++_dfn;
    for(int i = head[u]; i; i = e[i].nxt) {
        if((i ^ 1) == toe)
            continue;
        int v = e[i].v;
        if(!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])
                cut[i] = cut[i^1] = 1;
        } else
            low[u] = min(low[u], dfn[v]);
    }
}

void dfs(int u) {
    vis[u] = 1;
    ret ^= a[u];
    for(int i = head[u]; i; i = e[i].nxt) {
        if(cut[i])
            continue;
        int v = e[i].v;
        if(vis[v])
            continue;
        dfs(v);
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
        addedge(u, v);
        addedge(v, u);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i, 0);
    for(int i = 1; i <= n; i++)
        if(!vis[i]) {
            ret = 0;
            dfs(i);
            ans.push_back(ret);
        }
    sort(ans.begin(), ans.end());
    for(int t : ans)
        cout << t << '\n';
    return 0;
}
