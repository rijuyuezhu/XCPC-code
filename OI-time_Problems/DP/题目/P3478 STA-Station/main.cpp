// https://www.luogu.com.cn/problem/P3478
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
const int MAXN = 1e6 + 5;
int n;
ll dp[MAXN], sz[MAXN];
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].nxt = head[v]; head[v] = cnt;
}
ll dfs1(int u, ll dep, int f) {
    ll ans = dep;
    sz[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == f) continue;
        ans += dfs1(v, dep + 1, u);
        sz[u] += sz[v];
    }
    return ans;
}
void dfs2(int u, int f) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == f) continue;
        dp[v] = dp[u] + n - 2 * sz[v];
        dfs2(v, u);
    }
}
int main() {
    n = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v);
    }
    dp[1] = dfs1(1, 0, 0);
    dfs2(1, 0);
    int ans = 1;
    for(int i = 2; i <= n; i++)
        if(dp[i] > dp[ans]) ans = i;
    printf("%d\n", ans);
    return 0;
}