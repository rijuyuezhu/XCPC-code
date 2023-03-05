//http://poj.org/problem?id=3678
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
const int MAXM = 4e6 + 5;
struct Edge {
    int v, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
int n, m;

int dfn[MAXN], low[MAXN], tim;
int ins[MAXN], stk[MAXN], stp;
int bel[MAXN], gg;
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
    n = read(); //the num of nodes is in [0, n); then become [0, 2n)
    m = read();
    for(int i = 1; i <= m; i++) {
        int a = read(), b = read(), c = read();
        char op[10]; scanf("%s", op);
        //a op b = c
        if(op[0] == 'A') {//a and b = c
            if(c == 0) {
                //if a=1 then b=0; if b=1 then a=0
                addedge(a+n, b); addedge(b+n, a);
            } else {
                //a,b cannot be 0; so we let them become impossible
                addedge(a, a+n); addedge(b, b+n);
            }
        } else if(op[0] == 'O') {//a or b = c
            if(c == 0) {
                //cannot be 1
                addedge(a+n, a); addedge(b+n, b);
            } else {
                //a=0->b=1; b=0->a=1
                addedge(a, b+n); addedge(b, a+n);
            }
        } else {//a xor b = c
            if(c == 0) {
                //a=0->b=0; a=1->b=1; b is also
                addedge(a, b); addedge(a+n, b+n);
                addedge(b+n, a+n); addedge(b, a); 
            } else {
                //a=0->b=1; a=1->b=0; b is also
                addedge(a, b+n); addedge(a+n, b);
                addedge(b, a+n); addedge(b+n, a);
            }
        }
    }
    for(int i = 0; i < 2 * n; i++)
        if(!dfn[i]) tarjan(i);
    bool flag = 1;
    for(int i = 0; i < n; i++)
        if(bel[i] == bel[i + n]) {
            flag = 0;
            break;
        }
    printf(flag ? "YES\n" : "NO\n");
    return 0;
}