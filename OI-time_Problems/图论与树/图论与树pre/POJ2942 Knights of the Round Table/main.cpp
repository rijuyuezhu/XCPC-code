//http://poj.org/problem?id=2942
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
#define CLA(A, x) memset(A, x, sizeof A)
const int MAXN = 1005;
int n, m;
bool G[MAXN][MAXN];

int dfn[MAXN], low[MAXN], tim;
vector<int> dcc[MAXN]; int gg;
int stk[MAXN], stp;
int cut[MAXN];
void tarjan(int u, int rt) {
    dfn[u] = low[u] = ++tim;
    stk[++stp] = u;
    if(u == rt) {//single point
        bool fl = 1;
        for(int i = 1; i <= n; i++) if(G[u][i]) {fl = 0; break;}
        if(fl) {
            dcc[++gg].push_back(u);
            return;
        }
    }
    int flag = 0;
    for(int v = 1; v <= n; v++) if(G[u][v]) {
        if(!dfn[v]) {
            tarjan(v, rt);
            low[u] = min(low[u], low[v]);
            if(dfn[u] <= low[v]) {
                flag++;
                if(u != rt || flag > 1) cut[u] = 1;
                gg++;
                int now;
                do {
                    now = stk[stp--];
                    dcc[gg].push_back(now);
                }while(now != v);
                dcc[gg].push_back(u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}


int c[MAXN];
bool arr[MAXN];
bool iser;
bool canadd[MAXN];
void dfs(int u, int col) {
    c[u] = col;
    for(int v = 1; v <= n; v++) if(G[u][v] && arr[v]) {
        if(!c[v]) dfs(v, 3 - col);
        else if(c[v] == col) {
            iser = 0;
            return;
        }
    }
}


void init() {
    CLA(G, 1);
    for(int i = 1; i <= n; i++) G[i][i] = 0;
    CLA(dfn, 0); CLA(low, 0); tim = 0;
    for(int i = 1; i <= n; i++) dcc[i].clear();
    gg = 0;
    CLA(stk, 0); stp = 0;
    CLA(cut, 0);
    CLA(c, 0); CLA(arr, 0);
    CLA(canadd, 0);
}
void solve() {
    for(int i = 1; i <= m; i++) {
        int k1 = read(), k2 = read();
        G[k1][k2] = G[k2][k1] = 0;
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan(i, i);
    for(int i = 1; i <= gg; i++) {
        CLA(c, 0); CLA(arr, 0); iser = 1;
        for(int j = 0, up = dcc[i].size(); j < up; j++) arr[dcc[i][j]] = 1;
        dfs(dcc[i][0], 1);
        if(!iser) {
            for(int j = 0, up = dcc[i].size(); j < up; j++) canadd[dcc[i][j]] = 1;
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) if(!canadd[i]) ans++;
    printf("%d\n", ans);

}
int main() {
    while(1) {
        n = read(), m = read();
        if(!n && !m) return 0;
        init();
        solve();
    }
    return 0;
}