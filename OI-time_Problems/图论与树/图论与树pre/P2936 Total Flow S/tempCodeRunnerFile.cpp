// https://www.luogu.com.cn/problem/P2936
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
const int MAXN = 705;
const int MAXP = 65;
char readc() {
    char c = getchar();
    while(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) c = getchar();
    return c;
}
int transfer(char c) {
    if(c >= 'A' && c <= 'Z') return c - 'A' + 1;
    if(c >= 'a' && c <= 'z') return c - 'a' + 27;
}
int n;
const int INF = 1e9;
struct Edge {
    int v, w, nxt;
}e[MAXN << 1];
int head[MAXP], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}

int d[MAXP], s, t;
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
            e[i].w -= k;
            e[i^1].w += k;
            rest -= k;
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
    n = read();
    for(int i = 1; i <= n; i++) {
        int u = transfer(readc()), v = transfer(readc()), w = read();
        addedge(u, v, w); addedge(v, u, 0);
    }
    s = transfer('A'), t = transfer('Z');
    printf("%d\n", dinic());
    return 0;
}