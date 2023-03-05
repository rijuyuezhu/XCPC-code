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
const int INF = 0x3f3f3f3f;
int n, m;
struct Edge {
    int v, nxt, w;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}
queue<int> q;
int dist[MAXN], inq[MAXN];
int tot[MAXN];
bool spfa() {
    fill(dist + 1, dist + 1 + n, -INF);
    dist[0] = 0; tot[0] = 0;
    q.push(0); inq[0] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(dist[v] < dist[u] + e[i].w) {
                dist[v] = dist[u] + e[i].w;
                tot[v] = tot[u] + 1;
                if(tot[v] >= n + 1) return 0;
                if(!inq[v]) inq[v] = 1, q.push(v);
            }
        }
    }
    return 1;
}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int a = read(), b = read(), c = read();
            addedge(b, a, c);
        } else if(opt == 2) {
            int a = read(), b = read(), c = read();
            addedge(a, b, -c);
        } else {
            int a = read(), b = read();
            addedge(a, b, 0); addedge(b, a, 0);
        }
    }
    for(int i = 1; i <= n; i++)
        addedge(0, i, 0);
    printf(spfa() ? "Yes\n" : "No\n");
    return 0;
}