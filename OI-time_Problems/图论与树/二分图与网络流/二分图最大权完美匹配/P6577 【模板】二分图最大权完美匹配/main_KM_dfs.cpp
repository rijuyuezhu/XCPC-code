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
const int MAXN = 505;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, match[MAXN], vx[MAXN], vy[MAXN];
ll e[MAXN][MAXN], slack[MAXN], lx[MAXN], ly[MAXN];
bool dfs(int u) {
	vx[u] = 1;
	for(int v = 1; v <= n; v++) if(!vy[v]) {
		if(lx[u] + ly[v] == e[u][v]) {
			vy[v] = 1;
			if(!match[v] || dfs(match[v])) {
				match[v] = u;
				return 1;
			}
		} else slack[v] = min(slack[v], lx[u] + ly[v] - e[u][v]);
	}
	return 0;
}
void KM() {
	for(int i = 1; i <= n; i++) lx[i] = -INF, ly[i] = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) lx[i] = max(lx[i], e[i][j]);
	for(int i = 1; i <= n; i++)
		while(1) {
			for(int j = 1; j <= n; j++) vx[j] = vy[j] = 0, slack[j] = INF;
			if(dfs(i)) break;
			ll d = INF;
			for(int j = 1; j <= n; j++) if(!vy[j]) d = min(d, slack[j]);
			for(int j = 1; j <= n; j++) {
				if(vx[j]) lx[j] -= d;
				if(vy[j]) ly[j] += d;
			}
		}
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = -INF;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll w = read();
		e[u][v] = max(e[u][v], w);
	}
	KM();
	ll ans = 0;
	for(int i = 1; i <= n; i++) ans += lx[i] + ly[i];
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i++) printf("%d ", match[i]);
	return 0;
}
