// https://www.luogu.com.cn/problem/P2598
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
const int MAXP = 20005;
const int INF = 5e8;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int n, m, s, t;
int statu[105][105];
int num(int x, int y) {
    return (x - 1) * m + y;
}
struct Edge {
    int v, nxt, w;
}e[MAXP * 5];
int head[MAXP], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}



int d[MAXP];
bool bfs() {
    memset(d, 0x00, sizeof d);
    queue<int> q;
    q.push(s); d[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(!d[v] && e[i].w) {
                d[v] = d[u] + 1;
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
        if(d[v] == d[u] + 1 && e[i].w) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) d[v] = 0;
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
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            statu[i][j] = read();
        }
    s = 0, t = num(n, m+1);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            if(statu[i][j] == 1) {
                addedge(s, num(i, j), INF);
                for(int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
                    if(statu[nx][ny] != 1) addedge(num(i, j), num(nx, ny), 1);
                }
            } else if(statu[i][j] == 2) {
                addedge(num(i, j), t, INF);
            } else {
                for(int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
                    if(statu[nx][ny] != 1) addedge(num(i, j), num(nx, ny), 1);
                }
            }
        }
    printf("%d\n", dinic());
    return 0;
}