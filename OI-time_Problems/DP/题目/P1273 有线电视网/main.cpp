// https://www.luogu.com.cn/problem/P1273
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
const int MAXN = 3005;
const int INF = 1e9;
int n, m;
struct Edge {
    int v, w, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}
int mon[MAXN];
int dp[MAXN][MAXN];
int dfs(int u) {
    if(u >= n-m+1) {
        dp[u][0] = 0; dp[u][1] = mon[u];
        return 1;
    }
    dp[u][0] = 0;
    int sum = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v, w = e[i].w;
        int t = dfs(v);
        sum += t;
        for(int j = sum; j > 0; j--) {
            for(int k = 1; k <= t; k++)
                if(dp[v][k] != -INF && dp[u][j-k] != -INF)
                    dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k] - w);
        }
    }
    return sum;
}
int main() {
    n = read(); m = read();
    for(int i = 1; i <= n-m; i++) {
        int k = read();
        for(int j = 1; j <= k; j++) {
            int v = read(), w = read();
            addedge(i, v, w);
        }
    }
    for(int i = n-m+1; i <= n; i++) mon[i] = read();
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= m; j++) 
            dp[i][j] = -INF;
    dfs(1);
    //for(int i = 1; i <= n; i++) printf("%d ", dp[i][1]);
    for(int i = m; i >= 0; i--)
        if(dp[1][i] >= 0) {
            printf("%d\n", i);
            break;  
        }
    return 0;
}