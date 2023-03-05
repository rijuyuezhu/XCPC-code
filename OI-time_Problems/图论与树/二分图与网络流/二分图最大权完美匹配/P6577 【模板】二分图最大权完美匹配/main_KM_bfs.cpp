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
const int MAXN = 505;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, vx[MAXN], vy[MAXN], px[MAXN], py[MAXN], pre[MAXN];
ll e[MAXN][MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
queue<int> que;
void aug(int v) {
	while(v) {
		int t = px[pre[v]];
		px[pre[v]] = v;
		py[v] = pre[v];
		v = t;
	}
}
void bfs(int s) {
	for(int i = 1; i <= n; i++) vx[i] = vy[i] = 0, slack[i] = INF;
	que = queue<int>();
	que.push(s);
	while(1) {
		while(que.size()) {
			int u = que.front(); que.pop();
			vx[u] = 1;
			for(int v = 1; v <= n; v++) if(!vy[v]) {
				if(lx[u] + ly[v] - e[u][v] < slack[v]) {
					slack[v] = lx[u] + ly[v] - e[u][v];
					pre[v] = u;
					if(slack[v] == 0) {
						vy[v] = 1;
						if(!py[v]) {aug(v); return ;}
						else que.push(py[v]);
					}
				}
			}
		}
		ll d = INF;
		for(int i = 1; i <= n; i++) if(!vy[i]) d = min(d, slack[i]);
		for(int i = 1; i <= n; i++) {
			if(vx[i]) lx[i] -= d;
			if(vy[i]) ly[i] += d;
			else slack[i] -= d;
		}
		for(int i = 1; i <= n; i++) if(!vy[i]) {
			if(slack[i] == 0) {
				vy[i] = 1;
				if(!py[i]) {aug(i); return ;}
				else que.push(py[i]);
			}
		}
	}
}
void KM() {
	for(int i = 1; i <= n; i++) lx[i] = -INF, ly[i] = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) lx[i] = max(lx[i], e[i][j]);
	for(int i = 1; i <= n; i++) bfs(i);
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) e[i][j] = -INF;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll w = read();
		e[u][v] = max(e[u][v], w);
	}
	KM();
	ll ans = 0;
	for(int i = 1; i <= n; i++) ans += lx[i] + ly[i];
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i++) printf("%d ", py[i]);
	return 0;
}
