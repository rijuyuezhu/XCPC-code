#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 305, MAXM = 2.5e4;
const db eps = 1e-8, inf = 1e10;
const int INF = 0x3f3f3f3f;
int n, a[MAXN][MAXN], b[MAXN][MAXN];
int head[MAXN], ver[MAXM], nxt[MAXM], cnt, edg[MAXM], s, t, maxflow, pre[MAXN], incf[MAXN], inq[MAXN];
db cost[MAXM], maxcost, dist[MAXN];
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
queue<int> que;
void addedge(int u, int v, int w, db c) {
	ver[++cnt] = v; edg[cnt] = w; cost[cnt] = c; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cost[cnt] = -c; nxt[cnt] = head[v]; head[v] = cnt;
}
bool spfa() {
	for(int i = 1; i <= 2 * n + 2; i++) dist[i] = -inf, incf[i] = 0, inq[i] = 0, pre[i] = 0;
	que = queue<int>();
	dist[s] = 0; inq[s] = 1; incf[s] = INF;
	que.push(s);
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			if(edg[i] && dist[v] < dist[u] + cost[i]) {
				dist[v] = dist[u] + cost[i];
				pre[v] = i;
				incf[v] = min(incf[u], edg[i]);
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return dcmp(dist[t] - (-inf)) != 0;
}
void MCMF() {
	while(spfa()) {
		maxflow += incf[t];
		maxcost += incf[t] * dist[t];
		int u = t;
		while(u != s) {
			int p = pre[u];
			edg[p] -= incf[t];
			edg[p^1] += incf[t];
			u = ver[p^1];
		}
	}
}
bool check(db m) {
	cnt = 1; s = 2 * n + 1, t = 2 * n + 2;
	for(int i = 1; i <= 2 * n + 2; i++) head[i] = 0;
	for(int i = 1; i <= n; i++) addedge(s, i, 1, 0), addedge(i+n, t, 1, 0);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			addedge(i, j+n, 1, a[i][j] - m * b[i][j]);
	maxcost = maxflow = 0;
	MCMF();
	return maxcost >= 0;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= n; j++)
			a[i][j] = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			b[i][j] = read();
	db l = 0, r = 1e4;
	while(r - l > eps) {
		db m = (l + r) / 2;
		if(check(m)) l = m;
		else r = m;
	}
	printf("%.6lf\n", l);
	return 0;
}
