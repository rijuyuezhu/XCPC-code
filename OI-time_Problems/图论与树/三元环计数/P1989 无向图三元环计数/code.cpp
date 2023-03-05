#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5, MAXE = 2e5 + 5;
int n, m;
struct Ed { int u, v; } ed[MAXE];
struct Edge { int v, nxt; } e[MAXE];
int head[MAXN], cnt, deg[MAXN], fl[MAXN], ans;
void addedge(int u, int v) { e[++cnt] = (Edge){v, head[u]}; head[u] = cnt; }

int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		deg[ed[i].u = read()]++; deg[ed[i].v = read()]++;
	}
	for(int i = 1; i <= m; i++) {
		if(deg[ed[i].u] < deg[ed[i].v] || (deg[ed[i].u] == deg[ed[i].v] && ed[i].u < ed[i].v))
			addedge(ed[i].u, ed[i].v);
		else addedge(ed[i].v, ed[i].u);
	}
	for(int u = 1; u <= n; u++) {
		for(int i = head[u]; i; i = e[i].nxt) fl[e[i].v] = u;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			for(int j = head[v]; j; j = e[j].nxt)
				if(fl[e[j].v] == u) ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
