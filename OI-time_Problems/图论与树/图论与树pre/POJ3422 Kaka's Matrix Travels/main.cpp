// http://poj.org/problem?id=3422
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
const int MAXN = 5005;
const int MAXM = 200005;
const int INF = 1e9;
int n, k;
int num(int x, int y, int mod) {
    return n * (x - 1) + y + mod * n * n;
}
struct Edge {
    int v, nxt, w, c;
}e[MAXM];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w, int c) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].c = c; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].c = -c; e[cnt].nxt = head[v]; head[v] = cnt;
}

int maxp, s, t, ans, dist[MAXN], vist[MAXN], incf[MAXN], pre[MAXN];
bool spfa() {
    fill(dist + 1, dist + 1 + maxp, -INF); 
    fill(vist + 1, vist + 1 + maxp, 0);
    queue<int> q;
    incf[s] = INF;
    q.push(s); vist[s] = 1; dist[s] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vist[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt) if(e[i].w) {
            int v = e[i].v;
            if(dist[v] < dist[u] + e[i].c) {
                dist[v] = dist[u] + e[i].c;
                incf[v] = min(incf[u], e[i].w);
                pre[v] = i;
                if(!vist[v]) vist[v] = 1, q.push(v);
            }
        }
    }
    return dist[t] != -INF;
}
void update() {
    int now = t;
    while(now != s) {
        int i = pre[now];
        e[i].w -= incf[t];
        e[i^1].w += incf[t];
        now = e[i^1].v;
    }
    ans += dist[t] * incf[t];
}
int main() {
    n = read(), k = read();
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++) {
            int c = read();
            addedge(num(i, j, 0), num(i, j, 1), 1, c);
            addedge(num(i, j, 0), num(i, j, 1), k - 1, 0);
            if(i < n) addedge(num(i, j, 1), num(i + 1, j, 0), k, 0);
            if(j < n) addedge(num(i, j, 1), num(i, j + 1, 0), k, 0);
        }
    s = 1; t = maxp = 2 * n * n;
    while(spfa()) update();
    printf("%d\n", ans);
    return 0;
}