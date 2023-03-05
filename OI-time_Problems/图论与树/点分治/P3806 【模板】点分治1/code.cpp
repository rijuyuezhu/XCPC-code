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
const int MAXN = 1e4 + 5;
const int MAXM = 105;
const int MAXV = 1e7 + 5;
const int INF = 0x3f3f3f3f;
int n, m, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], edg[MAXN << 1], cnt, mxk, ques[MAXM], ans[MAXM], tsz, sz[MAXN], mxsz[MAXN], rt, vis[MAXN], judge[MAXV], tmp[MAXN], tnum, dis[MAXN];
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void getrt(int u, int f) {
	sz[u] = 1; mxsz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v] || v == f) continue;
		getrt(v, u); sz[u] += sz[v]; mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], tsz - sz[u]);
	if(mxsz[u] < mxsz[rt]) rt = u;
}
void getdis(int u, int f) {
	if(dis[u] <= mxk) tmp[++tnum] = dis[u];
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		dis[v] = dis[u] + edg[i];
		getdis(v, u);
	}
}
void calc(int u) {
	static int que[MAXN];
	judge[0] = 1;
	int tl = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		tnum = 0; dis[v] = edg[i];
		getdis(v, u);
		for(int j = 1; j <= m; j++)
			for(int k = 1; k <= tnum; k++)
				if(ques[j] >= tmp[k]) ans[j] |= judge[ques[j] - tmp[k]];
		for(int j = 1; j <= tnum; j++)
			que[++tl] = tmp[j], judge[tmp[j]] = 1;
	}
	for(int i = 1; i <= tl; i++) judge[que[i]] = 0;
}
void solve(int u) {
	vis[u] = 1; calc(u);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		tsz = sz[v]; mxsz[rt = 0] = INF;
		getrt(v, u); solve(rt);
	}
}
int main() {
	//freopen("code.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	for(int i = 1; i <= m; i++) ques[i] = read(), mxk = max(mxk, ques[i]);
	tsz = n; mxsz[rt = 0] = INF;
	getrt(1, 0); solve(rt);
	for(int i = 1; i <= m; i++) printf(ans[i] ? "AYE\n" : "NAY\n");
	return 0;
}
