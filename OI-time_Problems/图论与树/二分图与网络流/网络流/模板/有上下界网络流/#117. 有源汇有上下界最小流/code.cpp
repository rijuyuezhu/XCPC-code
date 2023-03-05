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
const int MAXN = 50015, MAXM = 125015, MAXNODE = 50015, MAXEDGE = 400005;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, s, t, _s, _t, ver[MAXEDGE], nxt[MAXEDGE], cnt = 1, cur[MAXNODE], head[MAXNODE], d[MAXNODE], que[MAXNODE], hd, tl;
ll edg[MAXEDGE], addf[MAXNODE], ans;
void addedge(int u, int v, ll w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}

bool bfs() {
	memset(d, 0x00, sizeof d); hd = 1; tl = 0;
	memcpy(cur, head, sizeof cur);
	d[s] = 1; que[++tl] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(!d[ver[i]] && edg[i]) {
			int v = ver[i];
			d[v] = d[u] + 1;
			que[++tl] = v;
			if(v == t) return 1;
		}
	}
	return 0;
}
ll dfs(int u, ll flow) {
	if(u == t) return flow;
	ll rest = flow;
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i;
		if(edg[i] && d[ver[i]] == d[u] + 1) {
			int v = ver[i];
			ll k = dfs(v, min(rest, edg[i]));
			if(!k) d[v] = 0;
			edg[i] -= k; rest -= k; edg[i^1] += k;
		}
	}
	return flow - rest;
}
ll dinic() {
	ll maxflow = 0, flow;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
	return maxflow;
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	_s = n+1; _t = n+2;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll lo = read(), hi = read();
		addedge(u, v, hi - lo); addf[u] -= lo; addf[v] += lo;
	}
	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i]);
		if(addf[i] > 0) addedge(_s, i, addf[i]), sum += addf[i];
	}
	addedge(t, s, INF);
	swap(s, _s); swap(t, _t);
	if(dinic() != sum) {
		printf("please go home to sleep\n");
		return 0;
	}
	ans = edg[cnt];
	edg[cnt] = edg[cnt^1] = 0;
	swap(s, _t); swap(t, _s);
	printf("%lld\n", ans - dinic());
	 
	return 0;
}
