#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 100005;
int n;
ll m;
ll c[MAXN], l[MAXN];
struct Edge {
    int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;  
}

namespace LeftistTree {
    int ls[MAXN], rs[MAXN], sz[MAXN], sum[MAXN], dis[MAXN], val[MAXN];
    int tot;
    int crenode(int v) {
        tot++;
        ls[tot] = rs[tot] = 0;
        sz[tot] = 1;
        sum[tot] = val[tot] = v;
        dis[tot] = 0;
        return tot;
    }
    int merge(int u, int v) {
        if(!u || !v) return u + v;
        if(val[u] < val[v]) swap(u, v);
        rs[u] = merge(rs[u], v);
        if(dis[ls[u]] < dis[rs[u]]) swap(ls[u], rs[u]);
        dis[u] = dis[rs[u]] + 1;
        sz[u] = sz[ls[u]] + sz[rs[u]] + 1;
        sum[u] = sum[ls[u]] + sum[rs[u]] + val[u];
        return u;
        
    }
    int pop(int u) {
        return merge(ls[u], rs[u]);
    }
}
using namespace LeftistTree;
int rk;
int rt[MAXN];
ll ans;
void dfs(int u) {
    rt[u] = crenode(c[u]);
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        dfs(v);
        rt[u] = merge(rt[u], rt[v]);
        while(sum[rt[u]] > m) rt[u] = pop(rt[u]);
    }
    ans = max(ans, sz[rt[u]] * l[u]);
}
int main() {
    n = read(), m = read(); dis[0] = -1;
    for(int i = 1; i <= n; i++) {
        int b = read();
        addedge(b, i);
        if(b == 0) rk = b;
        c[i] = read(), l[i] = read();
    }
    dfs(rk);
    printf("%lld\n", ans);
    return 0;
}