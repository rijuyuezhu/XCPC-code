#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

constexpr int MAXN = 5e5 + 5;
constexpr int MAXM = 4e6 + 5;

int n, m;
struct Edge {
    int v, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}

int dfn[MAXN], low[MAXN], _dfn, stk[MAXN], top;
vector<vector<int> > dcc;//v-dcc

void tarjan(int u, int fa, int rt) {
    dfn[u] = low[u] = ++_dfn;
    stk[++top] = u;
    if(u == rt && !head[u]) {
        dcc.push_back(vector<int>{u});
        return ;
    }
    int ch = 0;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa)
            continue;
        if(!dfn[v]) {
            ch++;
            tarjan(v, u, rt);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                dcc.push_back(vector<int>{});
                int t;
                do {
                    t = stk[top--];
                    dcc[(int)dcc.size()-1].push_back(t);
                }while(t != v);
                dcc[(int)dcc.size()-1].push_back(u);
            }
        } else
            low[u] = min(low[u], dfn[v]);
    } 
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if(u == v)
            continue; //cases that (u, u) and u is size 1
        addedge(u, v);
        addedge(v, u);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i, 0, i);
    cout << dcc.size() << '\n';
    for(const auto &t : dcc) {
        cout << t.size() << ' ';
        for(auto v : t)
            cout << v << ' ';
        cout << '\n';
    }
    return 0;
}
