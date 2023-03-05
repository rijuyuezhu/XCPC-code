#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 1e5 + 5;
constexpr int P = 998244353;
struct mint {
    int v;
    mint(int v = 0) : v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; a = a * a, n >>= 1) if(n & 1) ret = ret * a; return ret;}

int n;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}

mint f[MAXN];
int siz[MAXN];
mint g[MAXN], fac[MAXN], ifac[MAXN], invpow2[MAXN];

void dfs(int u, int fa) {
    f[u] = 1;
    siz[u] = 1;
    int tot = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v; if(v == fa) continue;
        dfs(v, u);
        f[u] = f[u] * f[v];
        siz[u] += siz[v];
        if(siz[v] & 1)
            ++tot;
    }
    f[u] = f[u] * g[tot];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
        fac[i] = fac[i-1] * i;
    ifac[n] = qpow(fac[n]);
    for(int i = n-1; i >= 0; i--)
        ifac[i] = ifac[i+1] * (i+1);
    invpow2[0] = 1; invpow2[1] = qpow(2);
    for(int i = 2; i <= n; i++)
        invpow2[i] = invpow2[i-1] * invpow2[1];
    g[0] = 1;
    for(int i = 2; i <= n+1; i += 2)
        g[i] = fac[i] * invpow2[i / 2] * ifac[i / 2];
    for(int i = 1; i <= n; i += 2)
        g[i] = g[i+1];
    dfs(1, 0);
    cout << f[1].v << endl;
    return 0;
}
