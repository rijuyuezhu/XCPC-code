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
int readspj() {
	char ch = getchar();
	for(; ch != '.' && ch != '#'; ch = getchar());
	return ch == '#';
}
const int MAXN = 55, MAXNODE = MAXN * MAXN + 5, MAXEDGE = 8 * MAXN * MAXN + 5, INF = 0x3f3f3f3f;
int n, mat[MAXN][MAXN];
struct Edge {
	int v, nxt, w, c;
}e[MAXEDGE];
int cnt = 1, head[MAXNODE], num, rid[MAXN][MAXN], cid[MAXN][MAXN], siz[MAXNODE], S, T, t, maxflow, mincost, ans[MAXNODE], emp;
void addedge(int u, int v, int w, int c) {
	e[++cnt] = (Edge){v, head[u], w, c}; head[u] = cnt;
	e[++cnt] = (Edge){u, head[v], 0, -c}; head[v] = cnt;
}

int dist[MAXNODE], inq[MAXNODE], incf[MAXNODE], pre[MAXNODE];
queue<int> que;
bool spfa() {
	for(int i = 1; i <= T; i++) dist[i] = incf[i] = INF, pre[i] = 0, inq[i] = 0;
	dist[S] = 0; que = queue<int>(), que.push(S); inq[S] = 1;
	while(que.size()) {
		int u = que.front(); que.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt) if(e[i].w) {
			int v = e[i].v;
			if(dist[v] > dist[u] + e[i].c) {
				dist[v] = dist[u] + e[i].c;
				incf[v] = min(incf[u], e[i].w);
				pre[v] = i;
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return dist[T] != INF;
}
void MCMF() {
	while(spfa()) {
		maxflow += incf[T];
		mincost += incf[T] * dist[T];
		int u = T;
		while(u != S) {
			int p = pre[u];
			e[p].w -= incf[T];
			e[p^1].w += incf[T];
			u = e[p^1].v;
		}
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) mat[i][j] = readspj();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) if(!mat[i][j]) {
			if(j == 1 || mat[i][j-1]) ++num;
			siz[num]++; emp++;
			rid[i][j] = num;
		}
	int _row = num;
	for(int j = 1; j <= n; j++)
		for(int i = 1; i <= n; i++) if(!mat[i][j]) {
			if(i == 1 || mat[i-1][j]) ++num;
			siz[num]++;
			cid[i][j] = num;
		}
	S = num + 1, t = num + 2, T = num + 3;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) if(!mat[i][j])
			addedge(rid[i][j], cid[i][j], 1, 0);
	for(int i = 1; i <= _row; i++)
		for(int j = 0; j < siz[i]; j++)
			addedge(S, i, 1, j);
	for(int i = _row + 1; i <= num; i++)
		for(int j = 0; j < siz[i]; j++)
			addedge(i, t, 1, j);
	maxflow = mincost = 0;
	for(int i = 1; i <= emp; i++) {
		addedge(t, T, 1, 0);
		MCMF();
		ans[i] = mincost;
	}
	int q = read();
	for(int i = 1; i <= q; i++) {
		int k = read();
		printf("%d\n", ans[k]);
	}
	return 0;
}
