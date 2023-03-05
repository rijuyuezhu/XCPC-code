// https://www.luogu.com.cn/problem/P1272
//1s, 125MB
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
const int MAXN = 155;
const int INF = 0x3f3f3f3f;
int n, p;
struct Edge {
    int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
int inde[MAXN],outde[MAXN];
int dp[MAXN][MAXN];
int rt;
int dfs(int u) {
    dp[u][1] = outde[u];
    int sum = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        int t = dfs(v);
        sum += t;
        for(int j = sum; j >= 1; j--)
            for(int k = 1, up = min(t, min(p, j - 1)); k <= up; k++)
                if(dp[v][k] != INF && dp[u][j-k] != INF)
                    dp[u][j] = min(dp[u][j], dp[v][k] + dp[u][j-k] - 1);
    }
    return sum;
}
int main() {
    n = read(); p = read();
    for(int i = 1; i < n; i++) {
        int f = read(), s = read();
        outde[f]++; inde[s]++;
        addedge(f, s);
    }
    memset(dp, 0x3f, sizeof dp);
    for(int i = 1; i <= n; i++)
        if(inde[i] == 0) {
            rt = i;
            break;
        }
    dfs(rt);
    int ans = dp[rt][p];
    for(int i = 1; i <= n; i++) ans = min(ans, dp[i][p] + 1);
    printf("%d\n", ans);
    return 0;
}