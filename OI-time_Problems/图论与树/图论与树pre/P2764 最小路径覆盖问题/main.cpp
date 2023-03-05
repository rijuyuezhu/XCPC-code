// https://www.luogu.com.cn/problem/P2764
/*
DAG最小路径覆盖=顶点数-最大匹配数=顶点数-最大流数

理解方法一（二分图）
路径数最小
=终点数最小
=二分图左边的非匹配点最多

理解方法二（网络流）
https://www.luogu.com.cn/blog/boshi/solution-p2764
*/
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
const int MAXN = 305;
const int MAXM = 30005;
const int INF = 0x3f3f3f3f;
int n, m, s, t;
struct Edge {
    int v, nxt, w;
}e[MAXM];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}
int d[MAXN], ans, upto[MAXN];
bool bfs() {
    memset(d, 0x00, sizeof d);
    queue<int> q;
    q.push(s); d[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(!d[v] && e[i].w) {
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int flow) {
    if(u == t) return flow;
    int rest = flow;
    for(int i = head[u]; i && rest; i = e[i].nxt) {
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].w) {
            int k = dfs(v, min(flow, e[i].w));
            if(!k) d[v] = 0;
            else {
                rest -= k;
                e[i].w -= k;
                e[i^1].w += k;
            }
        }
    }
    return flow - rest;
}
int dinic() {
    int flow, ans = 0;
    while(bfs())
        while(flow = dfs(s, INF)) ans += flow;
    return ans;
}

int getup(int u) {
    if(upto[u] == u) return u;
    return upto[u] = getup(upto[u]);
}
void dfs2(int u) {
    printf("%d ", u);
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == s || e[i].w) continue;
        dfs2(v - n);
        break;
    }
}
int main() {
    n = read(), m = read();
    /*
    1~n in
    n+1~2n put
    0 s
    2n+1 t
    */
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        addedge(u, v + n, 1);
    }
    s = 0, t = 2 * n + 1;
    for(int i = 1; i <= n; i++) addedge(s, i, 1), addedge(i + n, t, 1);
    ans = dinic();
    for(int i = 1; i <= n; i++) upto[i] = i;
    for(int u = 1; u <= n; u++)
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(v == s || e[i].w) continue;
            int fu = getup(u), fv = getup(v - n);
            if(fu != fv) upto[fv] = fu;
        }
    for(int i = 1; i <= n; i++)
        if(upto[i] == i) dfs2(i), printf("\n");
    printf("%d\n", n - ans);
    return 0;
}