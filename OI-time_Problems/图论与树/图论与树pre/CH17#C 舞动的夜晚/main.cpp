// http://noi-test.zzstep.com/contest/CH%20Round%20%2317/%E8%88%9E%E5%8A%A8%E7%9A%84%E5%A4%9C%E6%99%9A
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
const int MAXN = 3e4 + 5, MAXT = 5e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m, t;
struct Edge {
    int u, v, nxt, w, id;
}e[MAXT << 1];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w, int id = 0) {
    e[++cnt].u = u; e[cnt].v = v; e[cnt].w = w; e[cnt].id = id; e[cnt].nxt = head[u]; head[u] = cnt;
}
int S, T;
int d[MAXN];
queue<int> q;
bool bfs() {
    memset(d, 0x00, sizeof d);
    while(!q.empty()) q.pop();
    d[S] = 1, q.push(S);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(!d[v] && e[i].w) {
                d[v] = d[u] + 1;
                q.push(v);
                if(v == T) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int flow) {
    if(u == T) return flow;
    int rest = flow;
    for(int i = head[u]; i && rest; i = e[i].nxt) {
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].w) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) d[v] = 0;
            rest -= k;
            e[i].w -= k;
            e[i^1].w += k;
        }
    }
    return flow -= rest;
}
int dinic() {
    int flow, ans = 0;
    while(bfs())
        while(flow = dfs(S, INF)) ans += flow;
    return ans;
}
int dfn[MAXN], low[MAXN], tim;
int stk[MAXN], stp, ins[MAXN];
int bel[MAXN], gg;
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    ins[u] = 1; stk[++stp] = u;
    for(int i = head[u]; i; i = e[i].nxt) {
        if(!e[i].w) continue;
        int v = e[i].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        gg++;
        int now;
        do {
            now = stk[stp--]; ins[now] = 0;
            bel[now] = gg;
        }while(now != u);
    }
}
bool canedge[MAXT];
int main() {
    n = read(), m = read(), t = read();
    /*
    s:0
    left:1~n
    right:n+1~n+m
    t:n+m+1
    */
    S = 0, T = n + m + 1;
    for(int i = 1; i <= t; i++) {
        int u = read(), v = read() + n;
        addedge(u, v, 1, i); addedge(v, u, 0);
    }
    for(int i = 1; i <= n; i++) addedge(S, i, 1), addedge(i, S, 0);
    for(int i = n + 1; i <= n + m; i++) addedge(i, T, 1), addedge(T, i, 0);
    dinic();
    for(int i = 0; i <= n + m + 1; i++)
        if(!dfn[i]) tarjan(i);
    for(int i = 2; i <= cnt; i++) 
        if(e[i].id) {
            if(!e[i].w) canedge[e[i].id] = 1;
            else if(bel[e[i].u] == bel[e[i].v]) canedge[e[i].id] = 1;
        }
    int ans = 0;
    for(int i = 1; i <= t; i++) if(!canedge[i]) ans++;
    printf("%d\n", ans);
    for(int i = 1; i <= t; i++)
        if(!canedge[i]) printf("%d ", i);
    printf("\n");
    return 0;
}