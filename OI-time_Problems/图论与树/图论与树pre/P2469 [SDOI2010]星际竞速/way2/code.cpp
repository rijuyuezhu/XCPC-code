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
const int MAXN = 805, MAXM = 15005;
const int MAXNODE = 17005, MAXEDGE = 40005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cap[MAXEDGE], head[MAXNODE], cnt = 1, ans;
void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; edg[cnt] = w; cap[cnt] = c; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cap[cnt] = -c; nxt[cnt] = head[v]; head[v] = cnt;
}
int ansflow, mincost, inq[MAXNODE], dist[MAXNODE], incf[MAXNODE], pre[MAXNODE]; 
bool spfa() {
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq);
	queue<int> que;
	dist[s] = 0; inq[s] = 1;
	que.push(s);
	incf[s] = INF;
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				if(!inq[v]) que.push(v), inq[v] = 1;
				pre[v] = i; incf[v] = min(incf[u], edg[i]);
			}
		}
	}
	return dist[t] < 0;
}
void MCMF() {
	while(spfa()) {
		int now = t;
		ansflow += incf[t]; mincost += incf[t] * dist[t];
		while(now != s) {
			int p = pre[now];
			edg[p] -= incf[t]; edg[p^1] += incf[t];
			now = ver[p^1];
		}
	}
}


int main() {
	n = read(); m = read();
	s = n+n+1, t = n+n+2;
	for(int i = 1; i <= n; i++) {
		int c = read();
		addedge(s, i, 1, 0);
		addedge(i+n, t, 1, -c);
		ans += c;
	}
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), c = read();
		if(u > v) swap(u, v);
		addedge(u, v+n, 1, c);
	}
	MCMF();
	printf("%d\n", ans + mincost);

	return 0;
}
