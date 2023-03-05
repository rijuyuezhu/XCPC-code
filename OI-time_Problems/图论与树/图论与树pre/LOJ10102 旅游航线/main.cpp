//https://loj.ac/problem/10102
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
const int MAXN = 30005;
const int MAXM = 30005;
struct Edge {
    int v, nxt;
}e[MAXM << 1];
bool bridge[MAXM << 1];
int head[MAXN], cnt = 1;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int m, n;
int dfn[MAXN], low[MAXN], tim;
void tarjan(int u, int in_e) {
    dfn[u] = low[u] = ++tim;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v])
                bridge[i] = bridge[i ^ 1] = 1;
        } else if(i != (in_e ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
}
int main() {
    while(1) {
        n = read(), m = read();
        if(!n && !m) break;
        memset(head, 0x00, sizeof head); cnt = 1;
        memset(dfn, 0x00, sizeof dfn);
        memset(low, 0x00, sizeof low); tim = 0;
        memset(bridge, 0x00, sizeof bridge); 
        for(int i = 1; i <= m; i++) {
            int a = read(), b = read();
            addedge(a, b), addedge(b, a);
        }
        for(int i = 1; i <= n; i++) 
            if(!dfn[i]) tarjan(i, 0);
        int ans = 0;
        for(int i = 2; i < cnt; i += 2)
            if(bridge[i]) ans++;
       printf("%d\n", ans);
    }
    return 0;
}