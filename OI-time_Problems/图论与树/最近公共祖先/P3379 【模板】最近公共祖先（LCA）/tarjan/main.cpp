//https://www.luogu.com.cn/problem/P3379
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
struct Que {
    int v, id, nxt;
}q[MAXM << 1];
int qhead[MAXN], qcnt;
int ans[MAXN];
void addque(int u, int v, int id) {
    q[++qcnt].id = id;
    q[qcnt].v = v;
    q[qcnt].nxt = qhead[u];
    qhead[u] = qcnt;
}
int upto[MAXN];
int find(int u) {
    if(upto[u] == u) return u;
    return upto[u] = find(upto[u]);
}
int vis[MAXN];
void tarjan(int u) {
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(vis[v]) continue;
        tarjan(v);
        upto[v] = u;
    }
    for(int i = qhead[u]; i; i = q[i].nxt) {
        int v = q[i].v, id = q[i].id;
        if(vis[v] == 2) ans[id] = find(v);
    }
    vis[u] = 2;
}
int main() {
    n = read(), m = read(), s = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v); addedge(v, u);
    }
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        if(u == v) ans[i] = u;
        else addque(u, v, i), addque(v, u, i);
    }
    for(int i = 1; i <= n; i++) upto[i] = i;
    tarjan(s);
    for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}