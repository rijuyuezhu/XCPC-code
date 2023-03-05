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
const int MAXN = 18;
const ll INF = 1e18;
ll c[MAXN + 1], f[1 << MAXN], g[1 << MAXN];
ll n, W, U;
int main() {
    n = read(); W = read(); U = (1 << n) - 1;
    fill(f + 1, f + U + 1, INF);
    fill(g + 1, g + U + 1, INF);
    for(int i = 1; i <= n; i++) c[i] = read();
    f[0] = 1; g[0] = 0;
    for(int s = 1; s <= U; s++) {
        for(int k = 1; k <= n; k++) 
            if((s >> (k-1)) & 1) {
                int t = s ^ (1 << (k-1));
                ll fn = f[t], gn = g[t] + c[k];
                if(gn > W) fn++, gn -= W;
                if(fn < f[s]) {
                    f[s] = fn;
                    g[s] = gn;
                } else if(fn == f[s]) g[s] = min(g[s], gn);
            }
    }
    printf("%d\n", f[U]);
    return 0;
}