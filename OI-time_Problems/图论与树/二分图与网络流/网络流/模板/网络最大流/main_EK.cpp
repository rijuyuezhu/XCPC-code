// https://www.luogu.com.cn/problem/P3376
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
const int MAXM = 5005;
const ll INF = 1e17;
int n, m, s, t;
struct Edge {
    int v, nxt; ll w;
}e[MAXM << 1];
int head[MAXN], cnt = 1;
void addedge(int u, int v, ll w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}
ll maxflow, incf[MAXN];
int pre[MAXN], vis[MAXN];
queue<int> q;

bool bfs() {
    memset(vis, 0x00, sizeof vis);
    while(!q.empty()) q.pop();
    q.push(s); incf[s] = INF;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) if(e[i].w) {
            int v = e[i].v;
            if(vis[v]) continue;
            incf[v] = min(e[i].w, incf[u]);
            pre[v] = i;
            q.push(v); vis[v] = 1;
            if(v == t) return 1;
        }
    }
    return 0;
}
void update() {
    int now = t;
    while(now != s) {
        int i = pre[now];
        e[i].w -= incf[t];
        e[i^1].w += incf[t];
        now = e[i^1].v;
    }
    maxflow += incf[t];
}
int main() {
    n = read(), m = read(), s = read(), t = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(); ll w = read();
        addedge(u, v, w);
        addedge(v, u, 0);
    }
    while(bfs()) update();
    printf("%lld\n", maxflow);
    return 0;
}