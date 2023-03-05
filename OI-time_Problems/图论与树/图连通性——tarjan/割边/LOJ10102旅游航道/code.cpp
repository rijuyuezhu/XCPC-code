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
const int MAXN = 30005, MAXM = 60005;
int n, m;
int head[MAXN], ver[MAXM], nxt[MAXM], cnt = 1, dfn[MAXN], low[MAXN], tim, bridge[MAXM];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void tarjan(int u, int in_e) {
	dfn[u] = low[u] = ++tim;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i];
		if(!dfn[v]) {
			tarjan(v, i);
			low[u] = min(low[u], low[v]);
			if(dfn[u] < low[v]) bridge[i] = bridge[i^1] = 1;
		} else if(i != (in_e^1)) low[u] = min(low[u], dfn[v]);
	}
}
int main() {
	while(1) {
		memset(head, 0x00, sizeof head); cnt = 1;
		memset(dfn, 0x00, sizeof dfn); memset(low, 0x00, sizeof low); memset(bridge, 0x00, sizeof bridge); tim = 0;
		n = read(); m = read();
		if(n == 0 && m == 0) break;
		for(int i = 1; i <= m; i++) {
			int u = read(), v = read();
			addedge(u, v); addedge(v, u);
		}
		for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, 0);
		int ans = 0;
		for(int i = 2; i <= cnt; i += 2) if(bridge[i]) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
