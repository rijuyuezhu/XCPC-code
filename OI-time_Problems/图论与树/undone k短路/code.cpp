#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
typedef double db;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5005, MAXM = 4e5 + 5;
const db inf = 1e40, eps = 1e-8;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
int n, m;
db E;
namespace Graph {
	struct Edge {
		int v, nxt;
		db w;
	}e[MAXM];
	int head[MAXN], cnt = 1; // 0 is positive, 1 is negative (mod 2)
	void addedge(int u, int v, db w) {
		e[++cnt] = (Edge){v, head[u], w}; head[u] = cnt;
		e[++cnt] = (Edge){u, head[v], w}; head[v] = cnt;
	}
} using namespace Graph;
namespace SP {
	struct QNode {
		db d; int u;
	};
	bool operator < (const QNode& a, const QNode& b) {return a.d > b.d;}
	priority_queue<QNode> que;
	db dist[MAXN];
	int vis[MAXN], pre[MAXN];
	void dijkstra() {
		for(int i = 1; i <= n; i++) dist[i] = inf, vis[i] = pre[i] = 0;
		dist[n] = 0; que.push((QNode){0.0, n});
		while(que.size()) {
			int u = que.top().u; que.pop();
			if(vis[u]) continue;
			vis[u] = 1;
			for(int i = head[u]; i; i = e[i].nxt) if(i & 1) {//neg
				int v = e[i].v;
				if(dcmp(dist[v] - (dist[u] + e[i].w)) > 0) {
					dist[v] = dist[u] + e[i].w; pre[v] = i; que.push((QNode){dist[v], v});
				}
			}
		}
	}
} using namespace SP;
namespace LeftyTree {
	struct Node {
		int ls, rs, dist, v; db val;
	}h[MAXM << 5];
	int tot;
	int crenode(int v, db val) {
		h[++tot] = (Node){0, 0, 1, v, val}; return tot;
	}
	int merge(int x, int y) {
		if(!x || !y) return x + y;
		if(dcmp(h[x].val - h[y].val) > 0) swap(x, y);
		int p = ++tot; h[p] = h[x];
		h[p].rs = merge(h[x].rs, y);
		if(h[h[p].ls].dist < h[h[p].rs].dist) swap(h[p].ls, h[p].rs);
		h[p].dist = h[h[p].rs].dist + 1;
		return p;
	}
	void ins(int& p, int v, db val) {
		p = merge(p, crenode(v, val));
	}
} using namespace LeftyTree;
int seq[MAXN], rt[MAXN];
bool cmp(int a, int b) {return dist[a] < dist[b];}
struct QN {
	db d; int u;
};
bool operator < (const QN& a, const QN& b) {return a.d > b.d;}
priority_queue<QN> pq;
int main() {
	n = read(), m = read(); scanf("%lf", &E);
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); db w; scanf("%lf", &w);
		if(u == n) continue;
		addedge(u, v, w);
	}
	dijkstra();
	for(int i = 1; i <= n; i++) seq[i] = i;
	sort(seq + 1, seq + 1 + n, cmp);
	for(int k = 1; k <= n; k++) {
		int u = seq[k];
		if(pre[u]) rt[u] = rt[e[pre[u]^1].v];
		for(int i = head[u]; i; i = e[i].nxt) if(~i & 1 && i != (pre[u]^1)) {
			int v = e[i].v; db delta = e[i].w - (dist[u] - dist[v]);
			ins(rt[u], v, delta);
		}
	}
	int ans = 0;
	if(dcmp(E-dist[1]) >= 0) ans++, E -= dist[1];
	if(rt[1]) pq.push((QN){h[rt[1]].val, rt[1]});
	while(pq.size()) {
		int u = pq.top().u; db ld = pq.top().d; pq.pop();
		//now sigma = dist[1] - ld
		if(dcmp(E-dist[1]-ld) < 0) break;
		E -= dist[1] + ld; ans++;
		int nxt = rt[h[u].v];
		if(nxt) pq.push((QN){ld + h[nxt].val, nxt});
		if(h[u].ls) pq.push((QN){ld - h[u].val + h[h[u].ls].val, h[u].ls});
		if(h[u].rs) pq.push((QN){ld - h[u].val + h[h[u].rs].val, h[u].rs});
	}
	printf("%d\n", ans);
	return 0;
}
