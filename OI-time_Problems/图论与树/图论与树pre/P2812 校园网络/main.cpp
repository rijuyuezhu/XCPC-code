// https://www.luogu.com.cn/problem/P2812
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
const int MAXN = 10005;
const int MAXM = 5000005;
int n;
struct Edge {
    int v, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
int dfn[MAXN], low[MAXN], tim;
int ins[MAXN], stk[MAXN], stp;
int bel[MAXN], gg, rd[MAXN], cd[MAXN];
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    ins[u] = 1; stk[++stp] = u;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        gg++;
        int now;
        do {
            now = stk[stp--]; ins[now] = 0;
            bel[now] = gg;
        }while(now != u);
    }
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        int x;
        while(1) {
            x = read();
            if(!x) break;
            addedge(i, x);
        }
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan(i);
    for(int u = 1; u <= n; u++)
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(bel[u] != bel[v]) cd[bel[u]]++, rd[bel[v]]++;
        }
    int cntc = 0, cntr = 0;
    for(int i = 1; i <= gg; i++) {
        if(!cd[i]) cntc++;
        if(!rd[i]) cntr++;
    }
    if(gg == 1) printf("1\n0\n");
    else printf("%d\n%d\n", cntr, max(cntr, cntc));
    return 0;
}