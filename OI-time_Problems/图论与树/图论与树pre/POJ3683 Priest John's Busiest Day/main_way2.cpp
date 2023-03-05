//http://poj.org/problem?aid=3683
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
const int MAXN = 2005;
const int MAXM = MAXN * MAXN * 2;
int n;
int S[MAXN], T[MAXN], D[MAXN];
struct Graph {
    struct Edge {
        int v, nxt;
    }e[MAXM];
    int head[MAXN], cnt;
    void addedge(int u, int v) {
        e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
    }
}g1, g2;


int readtime() {
    int h, m; scanf("%d:%d", &h, &m);
    return h * 60 + m;
}
void printtime(int t, char c) {
    printf("%02d:%02d%c", t / 60, t % 60, c);
}
bool overlap(int l1, int r1, int l2, int r2) {
    return !(r1 <= l2 || r2 <= l1);
}

//----
int dfn[MAXN], low[MAXN], tim;
int stk[MAXN], stp, ins[MAXN];
int bel[MAXN], gg;
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    ins[u] = 1; stk[++stp] = u;
    for(int i = g1.head[u]; i; i = g1.e[i].nxt) {
        int v = g1.e[i].v;
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

//---
int val[MAXN];

int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        S[i] = readtime(); T[i] = readtime(); D[i] = read();
    }
    //choose left is i, choose right is i+n
    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++) {
            if(overlap(S[i], S[i]+D[i], S[j], S[j]+D[j]))
                g1.addedge(i, j+n), g1.addedge(j, i+n);
            if(overlap(S[i], S[i]+D[i], T[j]-D[j], T[j]))
                g1.addedge(i, j), g1.addedge(j+n, i+n);
            if(overlap(T[i]-D[i], T[i], S[j], S[j]+D[j]))  
                g1.addedge(i+n, j+n), g1.addedge(j, i);
            if(overlap(T[i]-D[i], T[i], T[j]-D[j], T[j]))
                g1.addedge(i+n, j), g1.addedge(j+n, i);
        }
    for(int i = 1; i <= 2 * n; i++)
        if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++) {
        if(bel[i] == bel[i+n]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for(int i = 1; i <= n; i++) val[i] = bel[i] > bel[i+n], val[i+n] = !val[i];
    for(int i = 1; i <= n; i++) {
        if(val[i] == 0) printtime(S[i], ' '), printtime(S[i]+D[i], '\n');
        else printtime(T[i]-D[i], ' '), printtime(T[i],'\n');
    }
    return 0;
}