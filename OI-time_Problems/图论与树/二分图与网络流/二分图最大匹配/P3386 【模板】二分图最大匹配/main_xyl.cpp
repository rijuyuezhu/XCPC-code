// https://www.luogu.com.cn/problem/P3386
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
const int MAXN = 505, MAXE = 5e4 + 5;
int n, m, ed;
//O(ne)
//左连右
struct Edge {
    int v, nxt;
}e[MAXE];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
bool vis[MAXN];
int match[MAXN];
int ans = 0;
bool dfs(int u) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(!vis[v]) {
            vis[v] = 1;
            if(!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    n = read(), m = read(), ed = read();
    for(int i = 1; i <= ed; i++) {
        int u = read(), v = read();
        addedge(u, v);
    }
    for(int i = 1; i <= n; i++) {
        memset(vis, 0x00, sizeof vis);
        if(dfs(i)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}