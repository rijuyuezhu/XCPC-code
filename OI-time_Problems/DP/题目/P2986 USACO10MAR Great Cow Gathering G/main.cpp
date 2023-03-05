#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e5 + 5;
const ll INF = 1e18;
int c[MAXN];
int n;
struct Edge {
    int v, nxt;
    ll w;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u]; 
    head[u] = cnt;
}
ll dp[MAXN];//dp[i]:以i为根的不方便值
ll sum[MAXN];
void dfs1(int u, int fa, ll leng) {
    dp[1] += c[u] * leng;
    sum[u] = c[u];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == fa) continue;
        dfs1(v, u, leng + e[i].w);
        sum[u] += sum[v];
    }
}
void dfs2(int u, int fa) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; ll w = e[i].w; if(v == fa) continue;
        dp[v] = dp[u] + w * (sum[1] - 2 * sum[v]);
        dfs2(v, u);
    }
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) c[i] = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read(); ll w = read();
        addedge(u, v, w); addedge(v, u, w);
    }
    dfs1(1, 0, 0);
    ll ans = INF;
    dfs2(1, 0);
    for(int i = 1; i <= n; i++) ans = min(ans, dp[i]);
    printf("%lld\n", ans);
    return 0;
}