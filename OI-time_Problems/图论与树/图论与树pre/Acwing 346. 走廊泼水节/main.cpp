//https://www.acwing.com/problem/content/348/
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
const int MAXN = 6005;
int n;
struct Edge {
    int u, v;
    ll w;
    bool operator < (const Edge& y)const {
        return w < y.w;
    }
}e[MAXN];
int upto[MAXN], sz[MAXN];
int find(int x) {
    if(upto[x] == x) return upto[x];
    else return upto[x] = find(upto[x]);
}
ll ans;
void solve() {
    n = read();
    for(int i = 1; i <= n; i++) upto[i] = i, sz[i] = 1;
    for(int i = 1; i < n; i++) e[i].u = read(), e[i].v = read(), e[i].w = read();
    sort(e + 1, e + 1 + n - 1);
    ans = 0;
    for(int i = 1; i <= n - 1; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if(u == v) continue;
        ans += 1ll * (e[i].w + 1) * (sz[u] * sz[v] - 1);
        upto[v] = u;
        sz[u] += sz[v];
    }
    printf("%lld\n", ans);
}
int main() {
    int t = read();
    while(t--) solve();
    return 0;
}