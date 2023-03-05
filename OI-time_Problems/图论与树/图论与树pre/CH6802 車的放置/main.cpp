// http://noi-test.zzstep.com/contest/0x60%E3%80%8C%E5%9B%BE%E8%AE%BA%E3%80%8D%E4%BE%8B%E9%A2%98/6802%20%E8%BB%8A%E7%9A%84%E6%94%BE%E7%BD%AE
/*
二分图原因：
把行看成左边节点，列看成右边节点， 放车相当于连边
0要素：车不能同时在两行上，也不能同时在两列上
1要素：一行（列）只能与一列（行）连边
*/
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
const int MAXN = 205;
int n, m, t, ans;
int abd[MAXN][MAXN], match[MAXN];
bool vis[MAXN];
bool dfs(int u) {
    for(int v = 1; v <= m; v++) if(!abd[u][v]) {
        if(vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int main() {
    n = read(), m = read(), t = read();
    for(int i = 1, x, y; i <= t; i++) {
        x = read(), y = read();
        abd[x][y] = 1;
    }
    for(int i = 1; i <= n; i++) {
        memset(vis, 0x00, sizeof vis);
        if(dfs(i)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}