// https://www.luogu.com.cn/problem/P2472
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
const int MAXN = 25;
const int MAXP = 1005;
const int MAXM = 5e6 + 5;
const int INF = 5e8;
int r, c, d, s, t;
char h[MAXN][MAXN];
char p[MAXN][MAXN];
int num(int x, int y, int k) {
    return (x - 1) * c + y + r * c * k;
}
int distsqr(int x1, int y1, int x2, int y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}
struct Edge {
    int v, nxt, w;
}e[MAXM];
int head[MAXP], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}
int dep[MAXP];
bool bfs() {
    memset(dep, 0x00, sizeof dep);
    queue<int> q;
    q.push(s); dep[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(!dep[v] && e[i].w) {
                dep[v] = dep[u] + 1;
                q.push(v);
                if(v == t) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int flow) {
    if(u == t) return flow;
    int rest = flow;
    for(int i = head[u]; i && rest; i = e[i].nxt) {
        int v = e[i].v;
        if(dep[v] == dep[u] + 1 && e[i].w) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) dep[v] = 0;
            rest -= k;
            e[i].w -= k;
            e[i^1].w += k;
        }
    }
    return flow - rest;
}

int dinic() {
    int flow, ans = 0;
    while(bfs())
        while(flow = dfs(s, INF)) ans += flow;
    return ans;
}
int nbef = 0;
int main() {
    r = read(), c = read(), d = read();
    for(int i = 1; i <= r; i++) 
        scanf("%s", h[i] + 1);
    for(int i = 1; i <= r; i++)
        scanf("%s", p[i] + 1);
    s = 0, t = num(r, c+1, 1);
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++) {
            if(h[i][j] == '0') continue;
            addedge(num(i, j, 0), num(i, j, 1), h[i][j]-'0');
            if(p[i][j] == 'L') addedge(s, num(i, j, 0), 1), nbef++;
            for(int ii = 1; ii <= r; ii++)
                for(int jj = 1; jj <= c; jj++)
                    if(distsqr(i, j, ii, jj) <= d * d) {
                        addedge(num(i, j, 1), num(ii, jj, 0), INF);
                    }
            if(i <= d || r + 1 - i <= d || j <= d || c + 1 - j <= d) addedge(num(i, j, 1), t, INF);
        }
    printf("%d\n", nbef - dinic());
    return 0;
}