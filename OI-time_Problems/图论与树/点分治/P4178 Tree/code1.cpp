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
const int MAXN = 4e4 + 5, INF = 0x3f3f3f3f;
int n, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, edg[MAXN << 1], k, sz[MAXN], mxsz[MAXN], tsz, rt, vis[MAXN], d[MAXN], dnum, ans;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void getrt(int u, int f) {
	sz[u] = 1; mxsz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getrt(v, u); sz[u] += sz[v]; mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], tsz - sz[u]);
	if(mxsz[u] < mxsz[rt]) rt = u;
}
void getdis(int u, int f, int dis) {
	d[++dnum] = dis;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getdis(v, u, dis + edg[i]);
	}
}
int calc(int u, int dis) {
	int ans = 0; dnum = 0;
	getdis(u, 0, dis);
	sort(d + 1, d + 1 + dnum);
	for(int i = 1, j = dnum; i <= n && i <= j; i++) {
		while(d[i] + d[j] > k) j--;
		if(i <= j) ans += j - i;
	}
	return ans;
}
void solve(int u) {
	vis[u] = 1; ans += calc(u, 0);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		ans -= calc(v, edg[i]);
		tsz = sz[v]; mxsz[rt = 0] = INF;
		getrt(v, u); solve(rt);
	}
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	k = read();
	tsz = n; mxsz[rt = 0] = INF;
	getrt(1, 0); solve(rt);
	printf("%d\n", ans);
	return 0;
}
