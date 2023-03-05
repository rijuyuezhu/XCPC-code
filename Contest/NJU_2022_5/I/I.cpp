#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
const int MAXN = 37;
int n, m, P, w[MAXN], deg[MAXN], del[MAXN], c[MAXN], col;
vector<int> Bl[MAXN];
int ans;
vector<int> G[MAXN];
void delnode(int u) {
    del[u] = 1;
    for(auto v : G[u]) deg[v]--;
}
void undelnode(int u) {
    del[u] = 0;
    for(auto v : G[u]) deg[v]++;
}

void dye(int u, int C) {
    c[u] = C; Bl[C].push_back(u);
    for(auto v : G[u])
        if(!del[v] && !c[v])
            dye(v, C);
}

void calccr(int mul, vector<int>& ve) {

}
void calcln(int mul, vector<int>& ve) {
   stat 
}
void calc(int mul) {
    for(int i = 1; i <= n; i++)
        if(!del[i]) c[i] = 0;
    for(int i = 1; i <= n; i++)
        if(!del[i] && !c[i]) {
            Bl[++col].clear();
            dye(i, col);
            bool iscr = 1;
            for(auto v : Bl[col])
                if(deg[v] < 2) {
                    iscr = 0;
                    break;
                }
            if(iscr) calccr(mul, Bl[col]);
            else calcln(mul, Bl[col]);
        }

}
void dfs(int mul) {
    int num = 0;
    for(int i = 1; i <= n; i++)
        if(!del[i] && deg[i] > 2) {
            num = i;
            break;
        }
    if(!num) {
        calc(mul);
        return;
    }
    vector<int> d;
    delnode(num);
    dfs(1ll * mul * w[num] % P);
    for(auto v : G[num])
        if(!del[v]) {
            delnode(v);
            d.push_back(v);
        }
    dfs(mul);
    for(auto v : d) undelnode(v);
    undelnode(num);

}
void work(int te) {
    scanf("%d%d%d", &n, &m, &P);
    for(int i = 1; i <= n; i++) {
        int v; scanf("%d", &v);
        w[i] = v % P;
    }
    for(int i = 1; i <= n; i++) {
        G[i].clear();
        deg[i] = c[i] = 0;
    }
    ans = col = 0;
    for(int i = 1; i <= m; i++) {
        int u, v;
        G[u].push_back(v);
        G[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    dfs(1);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) work(i);
    return 0;
}
