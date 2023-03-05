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
const int MAXN = 2e4 + 5;
const int INF = 0x3f3f3f3f;
int n, head[MAXN], nxt[MAXN << 1], ver[MAXN << 1], edg[MAXN << 1], cnt, tsz, mxsz[MAXN], sz[MAXN], rt, vis[MAXN], d[3], ans;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
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
	d[dis]++;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v] || v == f) continue;
		getdis(v, u, (dis + edg[i]) % 3);
	}
}
int calc(int u, int w) {
	d[0] = d[1] = d[2] = 0;
	getdis(u, 0, w);
	return d[0] * d[0] + d[1] * d[2] * 2;
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
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read() % 3;
		addedge(u, v, w); addedge(v, u, w);
	}
	tsz = n; mxsz[rt = 0] = INF;
	getrt(1, 0); solve(rt);
	int u = ans, v = n * n, g = gcd(u, v);
	u /= g; v /= g;
	printf("%d/%d\n", u, v);
	return 0;
}
