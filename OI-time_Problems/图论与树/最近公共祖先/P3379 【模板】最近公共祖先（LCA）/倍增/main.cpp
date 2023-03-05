//https://www.luogu.com.cn/problem/P3379
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 500005;
const int MAXM = 500005;
int n, m, s;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int depth[MAXN];
int fa[MAXN][21];
void dfs(int u, int f) {
    depth[u] = depth[f] + 1;
    fa[u][0] = f;
    for(int i = 1; i <= 20; i++) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int i = head[u]; i; i = e[i].nxt) if(!depth[e[i].v]) {
        dfs(e[i].v, u);
    }
}
int lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    for(int i = 20; i >= 0; i--) 
        if(depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    if(u == v) return u;
    for(int i = 20; i >= 0; i--) 
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
int main() {
    n = read(), m = read(), s = read();
    for(int i = 1; i < n; i++) {
        int x = read(), y = read();
        addedge(x, y);
        addedge(y, x);
    }
    dfs(s, 0);
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        printf("%d\n",lca(u, v));
    }
    return 0;
}