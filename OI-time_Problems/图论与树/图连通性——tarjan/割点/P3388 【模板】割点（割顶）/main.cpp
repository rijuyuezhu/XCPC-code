//https://www.luogu.com.cn/problem/P3388
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
const int MAXN = 2e4 + 5;
const int MAXM = 2e5 + 5;
int n, m, head[MAXN], ver[MAXM], nxt[MAXM], cnt, dfn[MAXN], low[MAXN], tim, cut[MAXN];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void tarjan(int u, int rt) {
	int fl = 0;
	dfn[u] = low[u] = ++tim;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i];
		if(!dfn[v]) {
			tarjan(v, rt);
			low[u] = min(low[u], low[v]);
			if(dfn[u] <= low[v]) {
				fl++;
				if(u != rt || fl > 1) cut[u] = 1;
			}
		} else low[u] = min(low[u], dfn[v]);
	}
}
int main() {	
	n = read(); m = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, i);
	int ans = 0;
	for(int i = 1; i <= n; i++) if(cut[i]) ans++;
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++) if(cut[i]) printf("%d ", i);
	printf("\n");
	return 0;
}
