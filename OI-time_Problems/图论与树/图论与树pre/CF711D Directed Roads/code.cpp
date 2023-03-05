#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int MAXN = 2e5 + 5;
const int P = 1e9 + 7;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}

int n, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt = 1, ans;
int qpow(int a, int n) {
	int ret = 1;
	for(; n; n >>= 1, a = mul(a, a))
		if(n & 1) ret = mul(ret, a);
	return ret;
}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
int bl[MAXN], sz[MAXN], szinc[MAXN], col, vis[MAXN];
void dfs1(int u, int c) {
	bl[u] = c; sz[c]++;
	for(int i = head[u]; i; i = nxt[i]) if(!bl[ver[i]]) {
		int v = ver[i]; dfs1(v, c);
	}
}
bool dfs2(int u, int in_e) {
	if(vis[u]) {vis[u] = 2; return 1;}
	vis[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) if(i != (in_e^1)) {
		if(dfs2(ver[i], i)) {
			szinc[bl[u]]++;
			if(vis[u] == 1) {
				vis[u] = 2; return 1;
			} else return 0;

		}
	}
	return 0;
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		int v = read();
		addedge(i, v); addedge(v, i);
	}
	ans = 1;
	for(int i = 1; i <= n; i++) 
		if(!bl[i]) {
			col++;
			dfs1(i, col); dfs2(i, 0);
			ans = mul(ans, mul(qpow(2, sz[col] - szinc[col]), mns(qpow(2, szinc[col]), 2)));
		}
	printf("%d\n", ans);
	return 0;
}
