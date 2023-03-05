#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e6 + 5;
int n;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
ll sz[MAXN];
ll dep[MAXN];
ll dp[MAXN];
void dfs1(int u, int fa) {
    sz[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        sz[u] += sz[v];
    }
}
void dfs2(int u, int fa) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        dp[v] = dp[u] + sz[1] - 2 * sz[v];
        dfs2(v, u);
    }
}
int main() {
    n = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(1, 0);
    for(int i = 1; i <= n; i++) dp[1] += dep[i];
    dfs2(1, 0);
    int ans = 1;
    for(int i = 2; i <= n; i++) 
        if(dp[i] > dp[ans]) ans = i;
    printf("%d\n", ans);
    return 0;
}