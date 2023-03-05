//https://www.luogu.com.cn/problem/P6175
//Floyd
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
const int MAXN = 105;
const int MAXM = 5e3 + 5;
const ll INF = 1e15;
int n, m;
ll G[MAXN][MAXN], d[MAXN][MAXN];
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            G[i][j] = (i == j) ? 0 : INF;
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        ll w = read();
        G[u][v] = G[v][u] = min(G[u][v], w);
    }
    memcpy(d, G, sizeof d);
    ll ans = INF;
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i < k; i++)
            for(int j = i + 1; j < k; j++)
                ans = min(ans, G[i][k] + G[j][k] + d[i][j]);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    if(ans == INF) printf("No solution.\n");
    else printf("%lld\n", ans);
    return 0;
}