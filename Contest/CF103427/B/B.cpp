#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;
constexpr int MAXM = 2e5 + 5;
constexpr int B = 30;
int n, m;
struct Edge {
    int v, nxt, w;
}e[MAXM << 1];
int head[MAXN], cnt;
int fail, siz[2], col[MAXN];
ll ans;

void addedge(int u, int v, int w) {
    e[++cnt] = {v, head[u], w};
    head[u] = cnt;
}

void dfs(int u, int C, int b) {
    col[u] = C;
    siz[C]++;
    for(int i = head[u]; i && !fail; i = e[i].nxt) {
        int v = e[i].v, nc = C ^ ((e[i].w >> b) & 1);
        if(col[v] == -1) {
            dfs(v, nc, b);
        } else {
            if(nc != col[v])
                fail = 1;
        }
    }
}
int calc(int b) {
    for(int i = 1; i <= n; i++)
        col[i] = -1;
    int ret = 0;
    for(int i = 1; i <= n && !fail; i++)
        if(col[i] == -1) {
            siz[0] = siz[1] = 0;
            dfs(i, 0, b);
            ret += min(siz[0], siz[1]);
        }
    return fail ? 0 : ret;
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
        addedge(v, u, w);
    }
    fail = 0;
    ans = 0;
    for(int i = 0; i < B && !fail; i++)
        ans += (ll)calc(i) << i;
    if(fail) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
    return 0;
}
