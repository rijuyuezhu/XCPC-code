// http://poj.org/problem?id=3565
//KM

#include<cstdio>
#include<cstring>
#include<cmath>
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
const double INF = 1e18;
struct Node {
    double x, y;
    friend double dist(const Node& a, const Node& b) {
        return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
    }
};
int n;
Node uco[MAXN], vco[MAXN];
double e[MAXN][MAXN], la[MAXN], lb[MAXN], d[MAXN];
bool va[MAXN], vb[MAXN];
int match[MAXN], ans[MAXN];
bool equal(double a, double b) {return abs(a - b) < 1e-5;}

bool dfs(int u) {
    va[u] = 1;
    for(int v = 1; v <= n; v++) if(!vb[v]) {
        if(equal(0, la[u] + lb[v] - e[u][v])) {
            vb[v] = 1;
            if(!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        } else d[v] = min(d[v], la[u] + lb[v] - e[u][v]);
    }
    return 0;
}
void KM() {
    fill(la + 1, la + 1 + n, -INF);
    fill(lb + 1, lb + 1 + n, 0);
    for(int u = 1; u <= n; u++)
        for(int v = 1; v <= n; v++)
            la[u] = max(la[u], e[u][v]);
    
    for(int u = 1; u <= n; u++) {
        while(1) {
            fill(va + 1, va + 1 + n, 0);
            fill(vb + 1, vb + 1 + n, 0);
            fill(d + 1, d + 1 + n, INF);
            if(dfs(u)) break;
            double mind = INF;
            for(int i = 1; i <= n; i++) if(!vb[i]) mind = min(mind, d[i]);
            for(int i = 1; i <= n; i++) {
                if(va[i]) la[i] -= mind;
                if(vb[i]) lb[i] += mind;
            }
        }
    }
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) uco[i].x = read(), uco[i].y = read();
    for(int i = 1; i <= n; i++) vco[i].x = read(), vco[i].y = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            e[i][j] = -dist(uco[i], vco[j]);
    KM();
    for(int i = 1; i <= n; i++) ans[match[i]] = i;
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}