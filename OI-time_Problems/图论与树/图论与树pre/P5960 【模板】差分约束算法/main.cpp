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
const int MAXN = 1e4 + 5;
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
int main() {
    n = read(); m = read();
    for(int i = 1; i <= m; i++) {
        int c = read(), c1 = read(), y = read();
        addedge(c1, c, y);
    }
    for(int i = 1; i <= n; i++) addedge(0, i, 0);
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0; tot[0] = 0;
    q.push(0); inq[0] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(dist[v] > dist[u] + e[i].w) {
                dist[v] = dist[u] + e[i].w;
                tot[v] = tot[u] + 1;
                if(tot[v] >= n + 1) {
                    printf("NO\n");
                    return 0;
                }
                if(!inq[v]) inq[v] = 1, q.push(v);
            }
        }
    }
    for(int i = 1; i <= n; i++) printf("%d ", dist[i]);
    printf("\n");
    return 0;
}