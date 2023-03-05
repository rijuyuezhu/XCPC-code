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
const int MAXN = 305;
int n, m, k, nxt[MAXN * 2], ver[MAXN * 2], edg[MAXN * 2], head[MAXN], cnt, f[MAXN][MAXN][2], tmp[MAXN][2];
void mkmin(int &a, int b) {a = min(a, b);}
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
}

void dfs(int u, int fa) {
	f[u][0][0] = f[u][1][1] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa) {
		int v = ver[i], w = edg[i];
		dfs(v, u);
		memcpy(tmp, f[u], sizeof tmp);
		memset(f[u], 0x3f, sizeof f[u]);
		for(int s = 0; s <= k; s++)
			for(int t = 0; t <= s; t++) {
				mkmin(f[u][s][0], min(f[v][t][0] + tmp[s-t][0] + (m==2)*w, f[v][t][1] + tmp[s-t][0]));
				mkmin(f[u][s][1], min(f[v][t][0] + tmp[s-t][1], f[v][t][1] + tmp[s-t][1] + w));
			}
	}
}
int main() {
	n = read(), m = read(), k = read();
	for(int i = 1; i < n; i++) {
		int a = read(), b = read(), c = read();
		addedge(a, b, c); addedge(b, a, c);
	}
	if(n - k < m - 1) {
		printf("-1\n");
		return 0;
	}
	memset(f, 0x3f, sizeof f);
	dfs(1, 0);
	printf("%d\n", f[1][k][1]);
	return 0;
}
