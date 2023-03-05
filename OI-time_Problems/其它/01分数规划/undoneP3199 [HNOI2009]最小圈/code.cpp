#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
typedef double db;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 3005, MAXM = 1e4 + 5;
const db inf = 1e12, eps = 1e-9;
int n, m, head[MAXN], ver[MAXM], nxt[MAXM], cnt, tot[MAXN], inq[MAXN];
db edg[MAXM], dist[MAXN];
queue<int> que;
void addedge(int u, int v, db w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
bool check(db m) {
	que = queue<int>();
	for(int i = 1; i <= n; i++) tot[i] = 0, inq[i] = 0, dist[i] = inf;
	dist[1] = 0; tot[1] = 0; inq[1] = 1; que.push(1);
	while(que.size()) {
		int u = que.front(); que.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			db w = edg[i] - m;
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				tot[v] = tot[u] + 1;
				if(tot[v] >= n) return 1;
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return 0;
}
int main() {
	db l = 1e20, r = -1e20;
	n = read(); m = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); db w; scanf("%lf", &w);
		l = min(l, w); r = max(r, w);
		addedge(u, v, w);
	}
	while(r - l > eps) {
		db m = (l + r) / 2;
		if(check(m)) r = m;
		else  l = m;
	}
	printf("%.8lf\n", l);
	return 0;
}
