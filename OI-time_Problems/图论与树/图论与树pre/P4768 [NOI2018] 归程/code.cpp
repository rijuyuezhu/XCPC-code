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
/*
 * note:
 * n<=2e5
 * m<=4e5
 * Q<=4e5
 * may be boom int(edge weight)
 */
const int MAXN = 4e5 + 5, MAXM = 8e5 + 5, iINF = 0x3f3f3f3fll;
const ll lINF = 0x3f3f3f3f3f3f3f3fll;
int n, m, Q, K, S;
ll lans;
struct Graph {
	int ver[MAXM], nxt[MAXM], edg[MAXM], alt[MAXM], head[MAXN], cnt;
	void addedge(int u, int v, int w, int a) {
		ver[++cnt] = v; edg[cnt] = w; alt[cnt] = a; nxt[cnt] = head[u]; head[u] = cnt;
	}
	void clear() {
		memset(head, 0x00, sizeof head); cnt = 0;
	}
};
namespace SP {//Shortest Path
	struct QN {
		ll d; int u;
		bool operator < (const QN& b)const {return d > b.d;}
	};
	Graph g;
	ll dist[MAXN];
	int vis[MAXN];
	priority_queue<QN> pq;
	void work() {
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; pq.push((QN){0ll, 1});
		while(pq.size()) {
			int u = pq.top().u; pq.pop();
			if(vis[u]) continue;
            vis[u] = 1;
			for(int i = g.head[u]; i; i = g.nxt[i]) {
				int v = g.ver[i], w = g.edg[i];
				if(dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.push((QN){dist[v], v});
				}
			}
		}

	}
}
namespace KT {//Kruskal Tree
	int upto[MAXN], num, val[MAXN], leaf[MAXN], rt, fa[MAXN][20];
	ll mind[MAXN];
	struct Edge {int u, v, w, a;}e[MAXM];
	Graph tr;
	bool cmp(const Edge& A, const Edge& B) {return A.a > B.a;}
	int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
	void dfs(int u, int f) {
		fa[u][0] = f; mind[u] = leaf[u] ? SP::dist[u] : lINF;
		for(int k = 1; k < 20; k++) fa[u][k] = fa[fa[u][k-1]][k-1];
		for(int i = tr.head[u]; i; i = tr.nxt[i]) if(tr.ver[i] != f) {
			int v = tr.ver[i];
			dfs(v, u);
			mind[u] = min(mind[u], mind[v]);
		}
	}
	void build() {
		num = n;
		sort(e + 1, e + 1 + m, cmp);
		for(int i = 1; i <= n; i++) upto[i] = i, leaf[i] = 1, val[i] = iINF;
		for(int i = 1; i <= m; i++) {
			int fu = getup(e[i].u), fv = getup(e[i].v);
			if(fu == fv) continue;
			val[++num] = e[i].a; upto[num] = upto[fu] = upto[fv] = num;
			tr.addedge(fu, num, 0, 0); tr.addedge(num, fu, 0, 0);
			tr.addedge(fv, num, 0, 0); tr.addedge(num, fv, 0, 0);
		}
		rt = getup(1);
		dfs(rt, 0);
	}
	int query(int u, int p) {
		for(int i = 19; i >= 0; i--)
			if(fa[u][i] && val[fa[u][i]] > p)
				u = fa[u][i];
		return u;
	}
}
void clear_all();
int main() {
	int T = read();
	while(T--) {
		clear_all();
		n = read(), m = read();
		for(int i = 1; i <= m; i++) {
			int u = read(), v = read(), w = read(), a = read();
			KT::e[i] = (KT::Edge){u, v, w, a};
			SP::g.addedge(u, v, w, a); SP::g.addedge(v, u, w, a);
		}
		SP::work();
		KT::build();
		Q = read(); K = read(); S = read();
		for(int i = 1; i <= Q; i++) {
			int v = (read() + K * lans - 1) % n + 1, p = (read() + K * lans) % (S + 1);
			int t = KT::query(v, p);
			lans = KT::mind[t];
			printf("%lld\n", lans);
		}
	}
	return 0;
}

void clear_all() {
	n = m = Q = K = S = 0;
	lans = 0;
	using namespace SP;
	g.clear();
	memset(dist, 0x00, sizeof dist);
	memset(vis, 0x00, sizeof vis);
	while(pq.size()) pq.pop();
	using namespace KT;
	memset(upto, 0x00, sizeof upto);
	num = 0;
	memset(val, 0x00, sizeof val);
	memset(leaf, 0x00, sizeof leaf);
	rt = 0;
	memset(fa, 0x00, sizeof fa);
	memset(mind, 0x00, sizeof mind);
	tr.clear();	
}
