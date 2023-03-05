//https://www.luogu.com.cn/problem/P6192
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 105;
const int MAXM = 1005;
const int MAXK = 10, MAXU = 1 << 10;
const int INF = 0x3f3f3f3f;
int n, U, m, k, head[MAXM], ver[MAXM], nxt[MAXM], edg[MAXM], cnt, id[MAXK], dp[MAXN][MAXU];
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
struct QNode{int d, u;};
bool operator < (const QNode& a, const QNode& b) {return a.d > b.d;}
priority_queue<QNode> pq;
int vis[MAXN];
void dijkstra(int s) {
	memset(vis, 0x00, sizeof vis);
	while(pq.size()) {
		int u = pq.top().u; pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			if(dp[v][s] > dp[u][s] + edg[i]) {
				dp[v][s] = dp[u][s] + edg[i];
				pq.push((QNode){dp[v][s], v});
			}
		}
	}
}
int main() {
	n = read(), m = read(), k = read(); U = (1 << k) - 1;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	for(int i = 0; i < k; i++) id[i] = read();
	memset(dp, 0x3f, sizeof dp);
	for(int i = 0; i < k; i++)
		dp[id[i]][1 << i] = 0;
	for(int s = 1; s <= U; s++) {
		for(int i = 1; i <= n; i++) {
			for(int t = s & (s-1); t; t = s & (t-1))
				dp[i][s] = min(dp[i][s], dp[i][t] + dp[i][s^t]);
			if(dp[i][s] != INF) pq.push((QNode){dp[i][s], i});
		}
		dijkstra(s);
	}
	printf("%d\n", dp[id[0]][U]);
	return 0;
}
