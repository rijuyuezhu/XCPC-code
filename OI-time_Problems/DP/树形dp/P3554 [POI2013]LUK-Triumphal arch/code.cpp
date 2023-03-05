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
const int MAXN = 3e5 + 5;
int n, ver[MAXN << 1], nxt[MAXN << 1], head[MAXN << 1], cnt, k;
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
int dfs(int u, int f) {
	int ans = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i];
		ans += (1 + dfs(v, u));
	}
	return max(0, ans - k);
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	int l = 0, r = n-1, ans = -1;
	while(l <= r) {
		k = (l + r) >> 1;
		if(dfs(1, 0) == 0) {ans = k; r = k-1;}
		else l = k+1;
	}
	printf("%d\n", ans);
	return 0;
}
