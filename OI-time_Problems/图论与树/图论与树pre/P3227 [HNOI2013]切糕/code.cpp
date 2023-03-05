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
const int MAXN = 45, MAXNODE = 70005, MAXEDGE = MAXNODE * 10;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
const int INF = 0x3f3f3f3f;
int P, Q, R, D, val[MAXN][MAXN][MAXN], id[MAXN][MAXN][MAXN], num, s, t, nxt[MAXEDGE], edg[MAXEDGE], head[MAXNODE], ver[MAXEDGE], cnt = 1;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}

int que[MAXNODE], hd, tl, d[MAXNODE];
bool bfs() {
	memset(d, 0x00, sizeof d);
	que[hd = tl = 1] = s; d[s] = 1;
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
			int k = dfs(v, min(w, rest));
			if(!k) d[v] = 0;
			edg[i] -= k;
			edg[i^1] += k;
			rest -= k;
		}
	return flow - rest;
}

int dinic() {
	int ans = 0, flow;
	while(bfs()) {
		while(flow = dfs(s, INF)) 
			ans += flow;
	}
	return ans;
}
int main() {
	P = read(), Q = read(), R = read(), D = read();
	s = ++num; t = ++num;
	for(int k = 1; k <= R; k++)
		for(int i = 1; i <= P; i++)
			for(int j = 1; j <= Q; j++)
				val[i][j][k] = read(), id[i][j][k] = ++num;
	for(int i = 1; i <= P; i++)
		for(int j = 1; j <= Q; j++)
			addedge(s, id[i][j][1], INF);
	for(int k = 1; k < R; k++)
		for(int i = 1; i <= P; i++)
			for(int j = 1; j <= Q; j++)
				addedge(id[i][j][k], id[i][j][k+1], val[i][j][k]);
	for(int i = 1; i <= P; i++)
		for(int j = 1; j <= Q; j++)
			addedge(id[i][j][R], t, val[i][j][R]);
	for(int k = D+1; k <= R; k++)
		for(int i = 1; i <= P; i++)
			for(int j = 1; j <= Q; j++) {
				for(int p = 0; p < 4; p++) {
					int nx = i + dx[p], ny = j + dy[p];
					if(nx >= 1 && nx <= P && ny >= 1 && ny <= Q) {
						addedge(id[i][j][k], id[nx][ny][k - D], INF);
					}
				}
			}
	printf("%d\n", dinic());
	return 0;
}
