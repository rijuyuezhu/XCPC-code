//http://noi-test.zzstep.com/contest/CH%20Round%20%2356%20-%20%E5%9B%BD%E5%BA%86%E8%8A%82%E6%AC%A2%E4%B9%90%E8%B5%9B/%E5%BC%82%E8%B1%A1%E7%9F%B3
//时间戳+set大法
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e5 + 5;
struct Edge {
    int v, nxt;
    ll w;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int n;
int dfn[MAXN], tim;
int fa[MAXN][20], dep[MAXN];
ll dist[MAXN];
void dfs(int u, int f) {
    dfn[u] = ++tim;
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for(int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == f) continue;
        dist[v] = dist[u] + e[i].w;
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i--)
        if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 19; i >= 0; i--)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
ll routedis(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[lca(u, v)];
}
struct cmp {
    bool operator() (int a, int b)const {
        return dfn[a] < dfn[b];
    }
};
typedef set<int, cmp> myset;
myset st;
ll ans;
int main() {
    n = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read(); ll w = read();
        addedge(u, v, w); addedge(v, u, w);
    }
    dist[1] = 0;
    dfs(1, 0);
    int m = read();
    while(m--) {
        char opt[3];
        scanf("%s", opt);
        if(opt[0] == '+') {
            int x = read();
            st.insert(x);
            myset::iterator r = st.upper_bound(x);
            if(r == st.end()) r = st.begin();
            myset::iterator l = st.lower_bound(x);
            if(l == st.begin()) l = st.end();
            l--;
            ans -= routedis(*l, *r);
            ans += routedis(x, *r);
            ans += routedis(x, *l);

        } else if(opt[0] == '-') {
            int x = read();
            myset::iterator r = st.upper_bound(x);
            if(r == st.end()) r = st.begin();
            myset::iterator l = st.lower_bound(x);
            if(l == st.begin()) l = st.end();
            l--;
            ans += routedis(*l, *r);
            ans -= routedis(x, *r);
            ans -= routedis(x, *l);
            st.erase(x);
        } else {
            printf("%lld\n", ans / 2);
        }
    }
    return 0;
}