// https://www.luogu.com.cn/problem/P2016
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
const int MAXN = 1505;
int n;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].nxt = head[v]; head[v] = cnt;
}
int dp[MAXN][2];
void dfs(int u, int f) {
    dp[u][0] = 0; dp[u][1] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == f) continue;
        dfs(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        int u = read(), k = read();
        for(int j = 1; j <= k; j++) {
            int v = read();
            addedge(u, v);
        }
    }
    dfs(0, 0);
    printf("%d\n", min(dp[0][0], dp[0][1]));
    return 0;
}