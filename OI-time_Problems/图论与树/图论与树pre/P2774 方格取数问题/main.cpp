// https://www.luogu.com.cn/problem/P2774

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
const int MAXN = 105;
const int MAXP = 30005;
const int MAXM = 300005;
const int INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int m, n, s, t;
int num(int x, int y) {
    return (x - 1) * n + y;
}
struct Edge {
    int v, nxt, w;
}e[MAXM];
int head[MAXP], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}
int ans;

int d[MAXP];
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
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].w) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) d[v] = 0;
            rest -= k;
            e[i].w -= k;
            e[i ^ 1].w += k;
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
    m = read(), n = read();
    s = 0; t = m * n + 1;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++) {
            int a = read(); ans += a;
            if(((i + j) & 1) == 0) {
                addedge(s, num(i, j), a);
                for(int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if(nx < 1 || nx > m || ny < 1 || ny > n) continue;
                    addedge(num(i, j), num(nx, ny), INF);
                }
            } else addedge(num(i, j), t, a);
        }
    printf("%d\n", ans - dinic());
    return 0;
}