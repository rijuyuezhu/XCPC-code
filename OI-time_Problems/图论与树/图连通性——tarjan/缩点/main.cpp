#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e4 + 5;
const int MAXM = 1e5 + 5;
int n, m;
int w[MAXN];
struct Edge {
    int u, v, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].u = u;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dfn[MAXN], low[MAXN], tim;
int num[MAXN], numi;
int wnum[MAXN];
int stk[MAXN], stop, ins[MAXN];
void tarjan(int u) {
    dfn[u] = low[u] = tim;
    stk[++stop] = u; ins[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].nxt;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        numi++;
        int now;
        do {
            now = stk[stop--]; ins[now] = 0;
            num[now] = numi;
            wnum[numi] += w[now];
        }while(now != u);
    }
}
int f[MAXN];
int dfs(int u) {
    if(f[u] != -1) return f[u];
    f[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        f[u] = max(f[u], dfs(v));
    }
    f[u] += wnum[u];
    return f[u];
}
int ans;
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++) w[i] = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        addedge(u, v);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan(i);
    memset(head, 0x00, sizeof head); cnt = 0;
    for(int i = 1; i <= m; i++) 
        if(num[e[i].u] != num[e[i].v])
            addedge(num[e[i].u], num[e[i].v]);
    memset(f, -1, sizeof f);
    for(int i = 1; i <= numi; i++)
        ans = max(ans, dfs(i));
    printf("%d\n", ans);
    return 0;
}