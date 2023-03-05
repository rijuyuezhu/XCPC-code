#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1005, MAXM = 10005;
struct Edge {int v, nxt; ll c;}e[MAXM];
int n, m, s, t, k, fl[MAXN], head[MAXN], cnt;
void addedge(int u, int v, ll c) {e[++cnt] = (Edge){v, head[u], c}; head[u] = cnt;}
void work() {
	n = read(), m = read(), s = read(), t = read();
	cnt = 0; for(int i = 1; i <= n; i++) head[i] = fl[i] = 0;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll c = read();
		addedge(u, v, c);
	}
	
}
int main() {
	for(int t = read(); t; t--) work();
	return 0;
}
