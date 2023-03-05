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
const int MAXN = 2005, MAXNODE = 4015, MAXEDGE = 50005;
ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, s, t, head[MAXNODE], cnt = 1, inq[MAXNODE], pre[MAXNODE];
ll pr, d1, w1, d2, w2, r[MAXN], maxflow, mincost, dist[MAXNODE], incf[MAXNODE];
struct Edge {int v, nxt; ll w, c;}e[MAXEDGE];
void addedge(int u, int v, ll w, ll c) {
	e[++cnt] = (Edge){v, head[u], w, c}; head[u] = cnt;
	e[++cnt] = (Edge){u, head[v], 0, -c}; head[v] = cnt;
}
//1~n: night; n+1~n+n: day;
bool spfa() {
	queue<int> que;
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq); incf[s] = INF; que.push(s); inq[s] = 1; dist[s] = 0;
	while(que.size()) {
		int u = que.front(); que.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt) if(e[i].w) {
			int v = e[i].v;
			if(dist[v] > dist[u] + e[i].c) {
				dist[v] = dist[u] + e[i].c;
				incf[v] = min(e[i].w, incf[u]);
				pre[v] = i;
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return dist[t] != INF;
}
void MCMF() {
	mincost = maxflow = 0;
	while(spfa()) {
		mincost += incf[t] * dist[t]; maxflow += incf[t];
		int now = t;
		while(now != s) {
			int p = pre[now];
			e[p].w -= incf[t]; e[p^1].w += incf[t];
			now = e[p^1].v;
		}
	}
}
int main() {
	n = read(); s = n+n+1, t = n+n+2;
	for(int i = 1; i <= n; i++) r[i] = read();
	pr = read(); d1 = read(); w1 = read(); d2 = read(); w2 = read();
	for(int i = 1; i <= n; i++) {
		addedge(s, i+n, INF, pr); 
		addedge(i+n, t, r[i], 0);
		addedge(s, i, r[i], 0);
		if(i+d1 <= n) addedge(i, i+d1+n, INF, w1);
		if(i+d2 <= n) addedge(i, i+d2+n, INF, w2);
		if(i+1 <= n) addedge(i, i+1, INF, 0);
	}
	MCMF();
	printf("%lld\n", mincost);
	return 0;
}
