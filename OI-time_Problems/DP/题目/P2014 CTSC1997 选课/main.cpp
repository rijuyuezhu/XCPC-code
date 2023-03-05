#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 305, MAXM = 305;
const int INF = 0x3f3f3f3f;
struct Edge {
    int v, nxt;
}e[MAXN];
int head[MAXN], cnt;

void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int n, m;
int dp[MAXN][MAXM];//f[i][j]表示在i的子树中选择j科所能得到的最大学分
int s[MAXN];
void dfs(int u) {
    dp[u][0] = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        dfs(v);
        for(int j = m; j >= 0; j--)
            for(int k = 0; k <= j; k++)
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
        }
    if(u != 0)
        for(int i = m; i >= 1; i--) dp[u][i] = dp[u][i - 1] + s[u];
}
int main() {
    n = read(), m = read();
    for(int i = 0; i < MAXN; i++)
        for(int j = 0; j < MAXM; j++)
            dp[i][j] = -INF;
    for(int i = 1; i <= n; i++) {
        int f = read();
        s[i] = read();
        addedge(f, i);
    }
    dfs(0);
    printf("%d\n", dp[0][m]);
    return 0;
}