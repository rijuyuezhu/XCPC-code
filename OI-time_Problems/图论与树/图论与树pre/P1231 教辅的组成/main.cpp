// https://www.luogu.com.cn/problem/P1231
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
const int MAXN = 5e4 + 5;
const int MAXM = 2e5 + 5;
const int INF = 5e8 + 5;

int nb, nl, nd, m1, m2, s, t;
struct Edge {
    int v, nxt, w;
}e[MAXM];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
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
/*
s->l->b->d->t

lx:1~nl
book1:nl+1~nl+nb
book2:nl+nb+1~nl+2nb
dn:nl+2nb+1~nl+2nb+nd
s:0
t:nl+2nb+nd+1
*/
int main() {
    nb = read(), nl = read(), nd = read();
    m1 = read();
    for(int i = 1; i <= m1; i++) {
        int b = read(), l = read();
        addedge(l, b + nl, 1);
    }
    m2 = read();
    for(int i = 1; i <= m2; i++) {
        int b = read(), d = read();
        addedge(b + nl + nb, d + nl + 2*nb, 1);
    }
    for(int i = nl + 1; i <= nl + nb; i++) addedge(i, i + nb, 1);
    s = 0, t = nl + 2*nb + nd + 1;
    for(int i = 1; i <= nl; i++) addedge(s, i, 1);
    for(int i = nl + 2*nb + 1; i <= nl + 2*nb + nd; i++) addedge(i, t, 1);
    printf("%d\n", dinic());
    return 0;
}