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
const int MAXN = 100005;
const int MAXM = 300005;
const ll INF = 1e17;
int n, m;
struct Ed {
    int u, v;
    ll w;
    bool flag;
    bool operator < (const Ed& y)const {
        return w < y.w;
    }
}ed[MAXM];
int upto[MAXN];
int findup(int x) {
    if(x == upto[x]) return x;
    return upto[x] = findup(upto[x]);
}
ll sum;


struct Edge {
    int v, nxt;
    ll w;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dep[MAXN], f[MAXN][21];
ll g[MAXN][21], h[MAXN][21];
void dfs(int u, int fa) {
    for(int i = head[u]; i; i = e[i].nxt) if(e[i].v != fa) {
        int v = e[i].v; ll w = e[i].w;
        dep[v] = dep[u] + 1;
        f[v][0] = u;
        g[v][0] = w;
        h[v][0] = -INF;
        dfs(v, u);
    }
}
void calc() {
    for(int i = 1; i <= 20; i++)
        for(int u = 1; u <= n; u++) {
            f[u][i] = f[f[u][i-1]][i-1];
            g[u][i] = max(g[u][i-1], g[f[u][i-1]][i-1]);
            if(g[u][i-1] == g[f[u][i-1]][i-1])
                h[u][i] = max(h[u][i-1], h[f[u][i-1]][i-1]);
            else if(g[u][i-1] > g[f[u][i-1]][i-1])
                h[u][i] = max(h[u][i-1], g[f[u][i-1]][i-1]);
            else h[u][i] = max(g[u][i-1], h[f[u][i-1]][i-1]);
        }
}
int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20; i >= 0; i--)
        if(dep[f[u][i]] >= dep[v]) u = f[u][i];
    if(u == v) return u;
    for(int i = 20; i >= 0; i--)
        if(f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}
ll routefind(int u, int fu, ll abv) {
    ll ans = -INF;
    for(int i = 20; i >= 0; i--)
        if(dep[f[u][i]] >= dep[fu]) {
            if(abv == g[u][i]) ans = max(ans, h[u][i]);
            else ans = max(ans, g[u][i]);
            u = f[u][i];
        }
    return ans;
} 
ll ans;
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        ed[i].u = read(), ed[i].v = read(), ed[i].w = read();
    }
    sort(ed + 1, ed + 1 + m);
    for(int i = 1; i <= n; i++) upto[i] = i;
    for(int i = 1; i <= m; i++) {
        int u = findup(ed[i].u), v = findup(ed[i].v); ll w = ed[i].w;
        if(u == v) continue;
        sum += w;
        upto[u] = v;
        ed[i].flag = 1;
        addedge(ed[i].u, ed[i].v, w);//一定是原来的点建边！！！
        addedge(ed[i].v, ed[i].u, w);
    }
    dfs(1, 0);
    calc();
    ans = INF;
    for(int i = 1; i <= m; i++) if(!ed[i].flag) {
        int u = ed[i].u, v = ed[i].v; ll w = ed[i].w;
        int l = lca(u, v);
        ll du = routefind(u, l, w), dv = routefind(v, l, w);
        ans = min(ans, sum - max(du, dv) + w);
    }
    printf("%lld\n", ans);
    return 0;
}