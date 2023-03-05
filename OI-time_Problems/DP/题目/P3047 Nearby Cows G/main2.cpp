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
const int MAXN = 1e5 + 5;
const int MAXK = 25;
int n, k;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].nxt = head[v]; head[v] = cnt;
}
int c[MAXN];
int dp[MAXN][MAXK], ans[MAXN];
void dfs1(int u, int f) {
    dp[u][0] = c[u];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == f) continue;
        dfs1(v, u);
        for(int j = 1; j <= k; j++)
            dp[u][j] += dp[v][j-1];
    }
}
void turnto(int pre, int now) {//把根从pre换到now
    for(int i = 1; i <= k; i++)
        dp[pre][i] -= dp[now][i-1];
    for(int i = 1; i <= k; i++)
        dp[now][i] += dp[pre][i-1];
}
void dfs2(int u, int f) {
    for(int i = 0; i <= k; i++) ans[u] += dp[u][i];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == f) continue;
        turnto(u, v);
        dfs2(v, u);
        turnto(v, u);
    }
}
int main() {
    n = read(); k = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v);
    }
    for(int i = 1; i <= n; i++) c[i] = read();
    dfs1(1, 0);
    dfs2(1, 0);
    for(int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}