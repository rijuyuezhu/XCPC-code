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
const int MAXK = 25, MAXN = 1e3 + 5, MAXNODE = 1e3 + 105, MAXEDGE = 5e4 + 5, INF = 0x3f3f3f3f;
int K, n, m, head[MAXNODE], cnt = 1, ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], s, t, maxflow, d[MAXNODE], cur[MAXNODE];
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; head[v] = cnt;
}
bool bfs() {
	static int que[MAXNODE];
	int hd = 1, tl = 1; que[1] = s;
	memset(d, 0x00, sizeof d);
	memcpy(cur, head, sizeof cur);
	d[s] = 1;
	while(hd <= tl) {
		int u = que[hd++]; 
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(!d[v]) {
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
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i; int v = ver[i];
		if(d[v] == d[u] + 1 && edg[i]) {
			int k = dfs(v, min(flow, edg[i]));
			if(!k) d[v] = 0;
			edg[i] -= k; edg[i^1] += k; rest -= k;
		}
	}
	return flow - rest;
}
void dinic() {
	int flow = 0;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
}

/*
 * 1~K:type
 * K+1~K+n:ques
 * K+n+1:s
 * K+n+2:t
 */

int main() {
	K = read(); n = read(); s = K+n+1; t = K+n+2;
	for(int i = 1; i <= K; i++) {
		int w = read(); m += w;
		addedge(s, i, w);
	}
	for(int i = 1; i <= n; i++) {
		int p = read();
		for(int j = 1; j <= p; j++) {
			int id = read();
			addedge(id, i+K, 1);
		}
		addedge(i+K, t, 1);
	}
	dinic();
	if(maxflow != m) {printf("No Solution!\n"); return 0;}
	for(int u = 1; u <= K; u++) {
		printf("%d: ", u);
		for(int i = head[u]; i; i = nxt[i]) if(i % 2 == 0) {//reverse edg
			if(edg[i^1]) printf("%d ", ver[i]-K);
		}
		printf("\n");
	}
	return 0;
}
