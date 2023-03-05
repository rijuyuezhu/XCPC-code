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
const int MAXN = 12, MAXU = 1 << 12, MAXM = 1005, INF = 0x3f3f3f3f;
int n, m, U;
int G[MAXN][MAXN];
int f[MAXU][MAXN];
int g[MAXU][MAXU];
int dp[MAXU][MAXN];
int ans;
void work(int st) {
    memset(dp, 0x3f, sizeof dp);
    dp[1 << st][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int s = 0; s <= U; s++) {
            for(int t = s; t; t = (t - 1) & s) {
                if(g[t][s] != INF && dp[t][i-1] != INF) dp[s][i] = min(dp[s][i], dp[t][i-1] + g[t][s] * i);
            }
            if(g[0][s] != INF && dp[0][i-1] != INF) dp[s][i] = min(dp[s][i],dp[0][i-1] + g[0][s] * i);
        }
        ans = min(ans, dp[U][i]);
    }
}
int main() {
    n = read(), m = read(); U = (1 << n) - 1; 
    memset(G, 0x3f, sizeof G);
    for(int i = 1; i <= m; i++) {
        int u = read() - 1, v = read() - 1, w = read();
        G[u][v] = G[v][u] = min(G[u][v], w);
    }
    memset(f, 0x3f, sizeof f);
    for(int s = 0; s <= U; s++)
        for(int v = 0; v < n; v++)
            for(int u = 0; u < n; u++) if((s >> u) & 1){
                f[s][v] = min(f[s][v], G[u][v]);
            }
    memset(g, 0x00, sizeof g);
    for(int s = 0; s <= U; s++) {
        for(int t = s; t; t = (t - 1) & s) {
            int p = t ^ s;
            for(int u = 0; u < n; u++) if((p >> u) & 1) {
                g[t][s] = min(INF, g[t][s] + f[t][u]);
            }
        }
        for(int u = 0; u < n; u++) if((s >> u) & 1) g[0][s] = min(INF, g[0][s] + f[s][u]);
    }
    ans = INF;
    for(int st = 0; st < n; st++) work(st);
    printf("%d\n", ans);
    return 0;
}