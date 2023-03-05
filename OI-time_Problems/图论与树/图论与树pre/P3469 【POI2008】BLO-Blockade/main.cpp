//https://www.luogu.com.cn/problem/P3469
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
const int MAXM = 5e5 + 5;
int n, m;
struct Edge {
    int v, nxt;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dfn[MAXN], low[MAXN], tim;
bool iscut[MAXN];
int sz[MAXN];
ll ans[MAXN];
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    sz[u] = 1;
    int flag = 0;
    int apart = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            sz[u] += sz[v];
            if(dfn[u] <= low[v]) {
                flag++;
                ans[u] += 1ll * sz[v] * (n - sz[v]);
                apart += sz[v];
                if(u != 1 || flag > 1) iscut[u] = 1;
            }
        } else low[u] = min(low[u], dfn[v]);
    }
    if(iscut[u]) ans[u] += 1ll * (n - apart - 1) * (apart + 1) + n - 1;
    else ans[u] = 2 * (n - 1);
}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int a = read(), b = read();
        addedge(a, b); addedge(b, a);
    }
    tarjan(1);
    for(int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}
