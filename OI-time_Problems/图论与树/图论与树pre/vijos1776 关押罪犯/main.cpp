//https://vijos.org/p/1776
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
const int MAXN = 2e4 + 5;
const int MAXM = 1e5 + 5;
struct Edge {
    int v, w, nxt;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int n, m;

int lw;
int c[MAXN];
bool flag;
void dfs(int u, int col) {
    c[u] = col;
    for(int i = head[u]; i; i = e[i].nxt)
        if(e[i].w > lw) {
            if(!c[e[i].v]) dfs(e[i].v, 3-col);
            else if(c[e[i].v] == col) flag = 0;
        }
}

bool check(int mid) {
    lw = mid;
    memset(c, 0x00, sizeof c);
    flag = 1;
    for(int i = 1; i <= n; i++)
        if(!c[i]) dfs(i, 1);
    return flag;
}


int main() {
    n = read(), m = read();
    int mw = 0;
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        mw = max(mw, w);
        addedge(u, v, w); addedge(v, u, w);
    }

    int l = 0, r = mw, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {ans = mid, r = mid - 1;}
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
