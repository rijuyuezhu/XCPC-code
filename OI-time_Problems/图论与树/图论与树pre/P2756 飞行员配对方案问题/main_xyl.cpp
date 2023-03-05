// https://www.luogu.com.cn/problem/P2756
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
int m, n;
struct Edge {
    int v, nxt;
}e[MAXN * MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int match[MAXN], vis[MAXN], ans;
bool dfs(int u) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int pr[MAXN];
int main() {
    m = read(), n = read();
    while(1) {
        int u = read(), v = read();
        if(u == -1 && v == -1) break;
        addedge(u, v);
    }
    for(int i = 1; i <= m; i++) {
        memset(vis, 0x00, sizeof vis);
        if(dfs(i)) ans++;
    }
    for(int i = m + 1; i <= n; i++)
        if(match[i]) pr[match[i]] = i;
    printf("%d\n", ans);
    for(int i = 1; i <= m; i++)
        if(pr[i]) printf("%d %d\n", i, pr[i]);
    return 0;
}