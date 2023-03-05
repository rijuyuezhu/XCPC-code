#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 100005;
const int MAXK = 100005;
int n, k;
struct req {int ty, a, b;}r[MAXK];
struct Graph {
	int head[MAXN], nxt[MAXK << 1], ver[MAXK << 1], sm[MAXK << 1], cnt;
	void addedge(int u, int v, int t) {
		nxt[++cnt] = head[u]; ver[cnt] = v; sm[cnt] = t; head[u] = cnt;
	}
}g1, g2;

int dfn[MAXN], low[MAXN], tim;
int stk[MAXN], stp, ins[MAXN];
int scc[MAXN], scc_num;
void tarjan(int u, const Graph& g) {
	dfn[u] = low[u] = ++tim;
	stk[++stp] = u; ins[u] = 1;
	for(int i = g.head[u]; i; i = g.nxt[i]) {
		int v = g.ver[i];
		if(!dfn[v]) {
			tarjan(v, g);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		scc_num++;
		int t;
		do {
			t = stk[stp--]; ins[t] = 0;
			scc[t] = scc_num;
		}while(t != u);
	}
}

int deg[MAXN], que[MAXN], hd, tl, tot;
ll f[MAXN];

int main() {
	n = read(), k = read();
	for(int i = 1; i <= k; i++)	r[i].ty = read(), r[i].a = read(), r[i].b = read();
	for(int i = 1; i <= k; i++) {
		req t = r[i];
		if(t.ty == 1) g1.addedge(t.a, t.b, 1), g1.addedge(t.b, t.a, 1);
		if(t.ty == 3) g1.addedge(t.b, t.a, 1);
		if(t.ty == 5) g1.addedge(t.a, t.b, 1);
	}

	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, g1);
	
	for(int u = 1; u <= n; u++)
		for(int i = g1.head[u]; i; i = g1.nxt[i]) {
			int v = g1.ver[i];
			if(scc[u] != scc[v]) g2.addedge(scc[u], scc[v], 1), deg[scc[v]]++;
		}
	for(int i = 1; i <= k; i++) {
		req t = r[i];
		if(t.ty == 2) g2.addedge(scc[t.a], scc[t.b], 0), deg[scc[t.b]]++;
		if(t.ty == 4) g2.addedge(scc[t.b], scc[t.a], 0), deg[scc[t.a]]++;
	}
	hd = 1; tl = 0;
	for(int i = 1; i <= scc_num; i++)
		if(!deg[i]) f[i] = 1, que[++tl] = i, tot++;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = g2.head[u]; i; i = g2.nxt[i]) {
			int v = g2.ver[i];
			if(g2.sm[i]) f[v] = max(f[v], f[u]);
			else f[v] = max(f[v], f[u] + 1);
			if(!--deg[v]) que[++tl] = v, tot++;
		}
	}
	if(tot != scc_num) printf("-1\n");
	else {
		ll ans = 0;
		for(int i = 1; i <= n; i++) ans += f[scc[i]];
		printf("%lld\n", ans);
	}
	return 0;
}
