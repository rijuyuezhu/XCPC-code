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
const int MAXN = 105, MAXNODE = 30010, MAXEDGE = 5e5 + 5;
const int INF = 0x3f3f3f3f;
const int dx[5] = {0, 0, 1, -1, 0};
const int dy[5] = {1, -1, 0, 0, 0};
int n, m, s, t, num, id[MAXN][MAXN], ans;
int nxt[MAXEDGE], ver[MAXEDGE], edg[MAXEDGE], head[MAXNODE], cnt = 1;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}


int d[MAXNODE], que[MAXNODE], hd, tl;
bool bfs() {
	memset(d, 0x00, sizeof d);
	d[s] = 1;
	hd = tl = 1; que[tl] = s;
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
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i && rest; i = nxt[i])
		if(d[ver[i]] == d[u] + 1 && edg[i]) {
			int v = ver[i], w = edg[i];
			int k = dfs(v, min(rest, w));
			edg[i] -= k; edg[i^1] += k; rest -= k;
		}
	return flow - rest;
}

int dinic() {
	int ans = 0, flow;
	while(bfs()) {
		while(flow = dfs(s, INF)) ans += flow;
	}
	return ans;
}
int main() {
	n = read(), m = read();
	s = ++num; t = ++num;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			id[i][j] = ++num;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			addedge(s, id[i][j], w);
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			addedge(id[i][j], t, w);
		}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			int tmp = ++num;
			addedge(s, tmp, w);
			for(int k = 0; k < 5; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if(nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
					addedge(tmp, id[nx][ny], INF);
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			int tmp = ++num;
			addedge(tmp, t, w);
			for(int k = 0; k < 5; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if(nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
					addedge(id[nx][ny], tmp, INF);
				}
			}
		}
	}
	printf("%d\n", ans - dinic());

	return 0;
}
