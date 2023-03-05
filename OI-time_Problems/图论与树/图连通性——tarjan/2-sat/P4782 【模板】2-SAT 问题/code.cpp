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
const int MAXN = 2e6 + 5;
struct Edge {int v, nxt;} e[MAXN];
int n, m, head[MAXN], cnt;
void addedge(int u, int v) { e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;}
int dfn[MAXN], low[MAXN], tim, stk[MAXN], _stk, ins[MAXN], scc[MAXN], _scc, val[MAXN];
void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	stk[++_stk] = u; ins[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		++_scc;
		int t = 0;
		while(t != u) {
			t = stk[_stk--]; ins[t] = 0;
			scc[t] = _scc;
		}
	}
}
int main() {
	n = read(), m = read();
	// u refers to tr, u + n refers to fa
	for(int i = 1; i <= m; i++) {
		int u = read(), a = read(), v = read(), b = read();
		addedge(u + a * n, v + (b^1) * n);
		addedge(v + b * n, u + (a^1) * n);
	}
	for(int i = 1; i <= 2 * n; i++) if(!dfn[i]) tarjan(i);//here 2n
	int fl = 1;
	for(int i = 1; i <= n; i++) {
		if(scc[i] == scc[i+n]) {
			fl = 0; break;
		}
		if(scc[i] < scc[i+n]) val[i] = 1;
		else val[i] = 0;
	}
	if(fl) {
		printf("POSSIBLE\n");
		for(int i = 1; i <= n; i++) printf("%d ", val[i]);
		printf("\n");
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
