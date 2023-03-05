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
const int MAXN = 805;
const int MAXM = 15005;
const int MAXNODE = 1705;
const int MAXEDGE = 50005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, a[MAXN], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cap[MAXEDGE], head[MAXNODE], cnt = 1;

void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; cap[cnt] = c; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; cap[cnt] = -c; head[v] = cnt;
}
//s:2*n+1, t:2*n+2
//u:1~n
//u':n+1~n+n

int inq[MAXNODE], dist[MAXNODE], incf[MAXNODE], pre[MAXNODE], maxflow, mincost;
bool spfa() {
	memset(inq, 0x00, sizeof inq); memset(dist, 0x3f, sizeof dist);
	queue<int> que;
	que.push(s); inq[s] = 1; dist[s] = 0; incf[s] = INF;
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				incf[v] = min(incf[u], edg[i]);
				pre[v] = i;
				if(!inq[v]) que.push(v), inq[v] = 1;
			}
		}
	}
	return dist[t] != INF;
}
void upd() {
	int now = t;
	while(now != s) {
		int p = pre[now];
		edg[p] -= incf[t]; edg[p^1] += incf[t];
		now = ver[p^1];
	}
	maxflow += incf[t]; mincost += incf[t] * dist[t];
}
void MCMF() {
	while(spfa()) upd();
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	s = n+n+1, t = n+n+2;
	for(int i = 1; i <= n; i++) addedge(s, i, 1, 0);
	for(int i = n+1; i <= n+n; i++) addedge(i, t, 1, 0);
	for(int i = 1; i <= n; i++) addedge(s, i+n, 1, a[i]);
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		if(u > v) swap(u, v);
		addedge(u, v+n, 1, w);
	}
	MCMF();
	printf("%d\n", mincost);
	return 0;
}
