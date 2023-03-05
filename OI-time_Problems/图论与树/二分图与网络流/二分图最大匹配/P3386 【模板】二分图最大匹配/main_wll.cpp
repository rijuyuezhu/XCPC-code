// https://www.luogu.com.cn/problem/P3386
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
const int MAXN = 1005;
const int MAXE = 5e4 + 5;
const int INF = 5e8;
int n, m, nume;
struct Edge {
    int v, nxt, w;
}e[(MAXN + MAXE) * 2];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}

int s, t, d[MAXN];
queue<int> q;
bool bfs() {
    memset(d, 0x00, sizeof d);
    while(!q.empty()) q.pop();
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
            int k = dfs(v, min(rest, e[i].w));
            if(!k) d[v] = 0;
            rest -= k;
            e[i].w -= k;
            e[i^1].w += k;
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
int main() {
    n = read(), m = read(), nume = read();
    /*
    s:0
    left:1~n
    right:n+1~n+m
    t:n+m+1
    */
    s = 0, t = n + m + 1;
    for(int i = 1; i <= nume; i++) {
        int u = read(), v = read();
        addedge(u, v + n, 1); addedge(v + n, u, 0);
    }
    for(int i = 1; i <= n; i++) addedge(s, i, 1), addedge(i, s, 0);
    for(int i = n + 1; i <= n + m; i++) addedge(i, t, 1), addedge(t, i, 0);
    printf("%d\n", dinic());
    return 0;
}
