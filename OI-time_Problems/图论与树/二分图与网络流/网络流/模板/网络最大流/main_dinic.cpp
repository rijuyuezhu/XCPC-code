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
const int MAXN = 205;
const int MAXM = 5005;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, s, t;
struct Edge {
	int v, nxt;
	ll w;
}e[MAXM << 1];
int cur[MAXN], head[MAXN], cnt = 1;
void addedge(int u, int v, ll w) {
	e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
	e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}


int dep[MAXN], que[MAXN], hd, tl;
bool bfs() {
	memset(dep, 0x00, sizeof dep); hd = 1; tl = 0;
	memcpy(cur, head, sizeof cur);
	que[++tl] = s; dep[s] = 1;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if(e[i].w && !dep[v]) {
				dep[v] = dep[u] + 1;
				que[++tl] = v;
				if(v == t) return 1;
			}
		}
	}
	return 0;
}
ll dfs(int u, ll flow) {
	if(u == t) return flow;
	ll rest = flow;
	for(int i = cur[u]; i && rest; i = e[i].nxt) {
		cur[u] = i;
		int v = e[i].v;
		if(e[i].w && dep[v] == dep[u] + 1) {
			ll k = dfs(v, min(rest, e[i].w));
			if(!k) dep[v] = 0;
			e[i].w -= k;
			rest -= k;
			e[i ^ 1].w += k;
		}
	}
	return flow - rest;
}

ll dinic() {
	ll ans = 0, flow;
	while(bfs())
		while(flow = dfs(s, INF))
			ans += flow;
	return ans;
}
int main() {
	n = read(), m = read(), s = read(), t = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll w = read();
		addedge(u, v, w);
	}
	printf("%lld\n", dinic());
	return 0;
}
