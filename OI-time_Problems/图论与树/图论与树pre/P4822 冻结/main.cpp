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
const int MAXN = 55;
const int MAXM = 1005;
const int INF = 0x3f3f3f3f;
struct Edge {
    int v, nxt, w;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}
int n, m, K;
struct Node {
    int u, k, w;
    Node(int u, int k, int w) : u(u), k(k), w(w) {}
    bool operator < (const Node& B)const {
        return w > B.w;
    }
};
priority_queue<Node> pq;
int dis[MAXN][MAXN], vis[MAXN][MAXN];
int main() {
    n = read(), m = read(), K = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        addedge(u, v, w); addedge(v, u, w);
    }
    memset(dis, 0x3f, sizeof dis);
    dis[1][K] = 0; pq.push(Node(1, K, 0));
    while(!pq.empty()) {
        Node now = pq.top(); pq.pop();
        int u = now.u, k = now.k;
        if(vis[u][k]) continue;
        vis[u][k] = 1;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(dis[v][k] > dis[u][k] + e[i].w) {
                dis[v][k] = dis[u][k] + e[i].w;
                pq.push(Node(v, k, dis[v][k]));
            }
            if(k >= 1 && dis[v][k-1] > dis[u][k] + (e[i].w >> 1)) {
                dis[v][k-1] = dis[u][k] + (e[i].w >> 1);
                pq.push(Node(v, k-1, dis[v][k-1]));
            }
        }
    }
    int ans = INF;
    for(int i = 0; i <= K; i++) ans = min(ans, dis[n][i]);
    printf("%d\n", ans);
    return 0;
}
