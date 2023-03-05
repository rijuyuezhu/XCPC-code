#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef long double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1005;
const db eps = 1e-5, inf = 1e20;
int n, x[MAXN], y[MAXN], z[MAXN], vis[MAXN];
db len[MAXN][MAXN], cst[MAXN][MAXN], dist[MAXN];
db sqr(db x) {return x * x;}
db Abs(db x) {return x < 0 ? -x : x;}
db val(int x, int y, db m) {return cst[x][y] - m * len[x][y];}
bool check(db m) {
	for(int i = 1; i <= n; i++) vis[i] = 0, dist[i] = inf;
	dist[1] = 0;
	db ret = 0;
	for(int i = 1; i <= n; i++) {
		db mn = inf; int id = 0;
		for(int j = 1; j <= n; j++)
			if(!vis[j] && dist[j] < mn) id = j, mn = dist[j];
		ret += mn; vis[id] = 1;
		for(int j = 1; j <= n; j++) if(!vis[j])
			dist[j] = min(dist[j], val(id, j, m));
	}
	return ret <= 0;
}
int main() {
	while(1) {
		n = read();
		if(!n) break;
		for(int i = 1; i <= n; i++) x[i] = read(), y[i] = read(), z[i] = read();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j < i; j++)
				len[i][j] = len[j][i] = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j])),
				cst[i][j] = cst[j][i] = Abs(z[i] - z[j]);
		db l = 0, r = 2e10;
		while(r - l > eps) {
			db m = (l + r) / 2;
			if(check(m)) r = m;
			else l = m;
		}
		printf("%.3Lf\n", l);
	}
	return 0;
}
