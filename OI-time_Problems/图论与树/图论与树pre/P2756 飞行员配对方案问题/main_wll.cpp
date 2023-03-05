// https://www.luogu.com.cn/problem/P2756
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
const int MAXN = 205;
const int INF = 1e9;
int m, n;
int s, t;
struct Edge {
    int v, w, nxt, flag;
}e[40005];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w, int flag = 0) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; e[cnt].flag = flag; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; e[cnt].flag = 0; head[v] = cnt;
}

int d[MAXN];
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
    int ans = 0, flow;
    while(bfs())
        while(flow = dfs(s, INF)) ans += flow;
    return ans;
}
int main() {
    m = read(), n = read();
    while(1) {
        int u = read(), v = read();
        if(u == -1 && v == -1) break;
        addedge(u, v, 1, 1);
    }
    s = n + 1, t = n + 2;
    for(int i = 1; i <= m; i++) addedge(s, i, 1);
    for(int i = m + 1; i <= n; i++) addedge(i, t, 1);
    printf("%d\n", dinic());
    for(int i = 2; i <= cnt; i++)
        if(e[i].flag && e[i].w == 0) printf("%d %d\n", e[i^1].v, e[i].v);
    return 0;
}