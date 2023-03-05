//https://www.luogu.com.cn/problem/P3629
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
const int MAXN = 100005;
int n, K;
struct Edge {
    int v, nxt, w;
}e[MAXN << 1];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

int pre[MAXN];
int dist[MAXN], vis[MAXN];

int bfs(int st) {
    memset(vis, 0x00, sizeof vis);
    dist[st] = 0, vis[st] = 1, pre[st] = 0;
    int ans = st;
    queue<int> q;
    q.push(st);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) if(!vis[e[i].v]) {
            pre[e[i].v] = u;
            vis[e[i].v] = 1;
            dist[e[i].v] = dist[u] + e[i].w; 
            if(dist[e[i].v] > dist[ans]) ans = e[i].v;
            q.push(e[i].v);
        }
    }
    return ans;
}
void dfs(int u) {
    if(!pre[u]) return;
    for(int i = head[u]; i; i = e[i].nxt)
        if(e[i].v == pre[u]) {
            e[i].w = e[i^1].w = -1;
            dfs(e[i].v);
            break;
        }
}
int f[MAXN];
int L2;
void dp(int u, int fa) {
    for(int i = head[u]; i; i = e[i].nxt) if(e[i].v != fa) {
        int v = e[i].v;
        dp(v, u);
        L2 = max(L2, f[u] + f[v] + e[i].w);
        f[u] = max(f[u], f[v] + e[i].w);
    }
}
int main() {
    n = read(), K = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v, 1);
        addedge(v, u, 1);
    }
    int l = bfs(1);
    int r = bfs(l);
    int L1 = dist[r];
    if(K == 1) {
        printf("%d\n", 2 * (n - 1) - (L1 - 1));
        return 0;
    }
    dfs(r);//直径上边权改为-1
    dp(1, 0);
    printf("%d\n", 2 * (n - 1) - (L1 - 1) - (L2 - 1));
    return 0;
}