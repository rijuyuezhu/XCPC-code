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
const int MAXN = 1005;
const int MAXE = 6e5 + 5;

int m, n, s, t;
int a[MAXN], b[MAXN];
struct Edge {
	int v, nxt, w;
}e[MAXE];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
	e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
	e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}
void reset() {
	memset(head, 0x00, sizeof head); cnt = 0;
}
void work() {
	reset();
	m = read(), n = read(); s = 0; t = m + n + 1;
	for(int i = 1; i <= m; i++) a[i] = read();
	for(int i = 1; i <= n; i++) b[i] = read();
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			if(gcd(a[i], b[j]) > 1)
				addedge(i, j+m, 1);
	for(int i = 1; i <= m; i++) addedge(s, i, 1);
	for(int i = m+1; i <= m+n; i++) addedge(i, t, 1);
	printf("%d", dinic() * 2);
}:wq

int main() {
	int t = read();
	while(t--) work();
	return 0;
}
