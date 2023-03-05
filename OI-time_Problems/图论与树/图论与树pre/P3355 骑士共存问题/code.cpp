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
const int MAXN = 305;
const int MAXNODE = MAXN * MAXN;
const int MAXEDGE = 20 * MAXN * MAXN;
const int INF = 0x3f3f3f3f;
const int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
int n, m, s, t, tot;
int head[MAXNODE], cnt = 1, ver[MAXEDGE], nxt[MAXEDGE], cap[MAXEDGE];
bool ban[MAXN][MAXN];
int num(int x, int y) {return (x - 1) * n + y + 2;}
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; cap[cnt] = w; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; cap[cnt] = 0; head[v] = cnt;
}

int d[MAXNODE], que[MAXNODE], hd, tl;
bool bfs() {
	memset(d, 0x00, sizeof d);
	hd = 1; tl = 0;
	que[++tl] = s;
	d[s] = 1;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			if(cap[i] && !d[v]) {
				d[v] = d[u] + 1;
				que[++tl] = v;
				if(v == t) return 1;
			}
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i && rest; i = nxt[i]) {
		int v = ver[i];
		if(cap[i] && d[v] == d[u] + 1) {
			int k = dfs(v, min(rest, cap[i]));
			if(!k) d[v] = 0;
			cap[i] -= k;
			cap[i^1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int dinic() {
	int flow, ans = 0;
	while(bfs()) {
		while(flow = dfs(s, INF)) ans += flow;
	}
	return ans;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		ban[x][y] = 1;
	}
	s = 1, t = 2;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) if(!ban[i][j]) {
			tot++;
			if((i + j) & 1) {//right
				addedge(num(i, j), t, 1);
			} else {//left
				addedge(s, num(i, j), 1);
				for(int k = 0; k < 8; k++) {
					int nx = i + dx[k], ny = j + dy[k];
					if(nx < 1 || nx > n || ny < 1 || ny > n || ban[nx][ny]) continue;
					addedge(num(i, j), num(nx, ny), 1);
				}
			}
		}
	printf("%d\n", tot - dinic());
	return 0;
}
