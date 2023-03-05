#include<algorithm>
#include<cstdio>
#include<vector>
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
const int MAXN = 3e5 + 5, P = 1e9 + 7;//MAXN is 4 times bigger than number of node.
int MOD(int v) {return v >= P ? v - P : v;}
int n, m, q;
struct Ed {int u, v, w;}e[MAXN];
bool cmp(const Ed& a, const Ed& b) {return a.w < b.w;}
int num, upto[MAXN], val[MAXN];
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
vector<int> G[MAXN];
int st[MAXN][19], tim, lg2[MAXN], dfn[MAXN], dep[MAXN];
void Kruskal() {
	sort(e + 1, e + 1 + m, cmp);
	num = n;
	for(int i = 1; i <= n; i++) upto[i] = i;
	for(int i = 1; i <= m; i++) {
		int fu = getup(e[i].u), fv = getup(e[i].v);
		if(fu == fv) continue;
		++num; val[num] = e[i].w;
		G[num].push_back(fu), G[num].push_back(fv);
		upto[num] = upto[fu] = upto[fv] = num;
	}
}
void dfs(int u, int f) {
	st[++tim][0] = u; dep[u] = dep[f] + 1; dfn[u] = tim;
	for(int i = 0; i < (int)G[u].size(); i++) {
		int v = G[u][i];
		dfs(v, u);
		st[++tim][0] = u;
	}
}
int better(int u, int v) {return dep[u] < dep[v] ? u : v;}
void st_init() {
	lg2[0] = -1; for(int i = 1; i <= tim; i++) lg2[i] = lg2[i >> 1] + 1;
	for(int k = 1; (1 << k) <= tim; k++)
		for(int i = 1; i + (1 << k) - 1 <= tim; i++)
			st[i][k] = better(st[i][k-1], st[i + (1 << (k-1))][k-1]);
}
int Lca(int u, int v) {
	u = dfn[u]; v = dfn[v]; if(u > v) swap(u, v);
	int k = lg2[v-u+1]; return better(st[u][k], st[v - (1 << k) + 1][k]);
}
namespace myMk {
	int A, B, C, P;
	void init() {A = read(), B = read(), C = read(), P = read();}
	int rnd() {return A = (A * B + C) % P;}
} using myMk::rnd;
int main() {
	n = read(); m = read();
	for(int i = 1; i <= m; i++) e[i].u = read(), e[i].v = read(), e[i].w = read();
	Kruskal();
	dfs(num, 0); st_init();
	q = read(); myMk::init();
	int ans = 0;
	for(int i = 1; i <= q; i++) {
		int u = rnd() % n + 1, v = rnd() % n + 1;
		ans = MOD(ans + val[Lca(u, v)]);
	}
	printf("%d\n", ans);
	return 0;
}
