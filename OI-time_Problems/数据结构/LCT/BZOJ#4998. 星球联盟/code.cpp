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
const int MAXN = 2e5 + 5;
int n, m, q, upto[MAXN], sz[MAXN], upto2[MAXN];

int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
int getup2(int u) {return u == upto2[u] ? u : upto2[u] = getup2(upto2[u]);}
#define ls ch[0]
#define rs ch[1]
struct Node {int ch[2], fa, rev;}e[MAXN];
int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
int idy(int p) {return e[e[p].fa].rs == p;}
void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
void psd(int p) {if(e[p].rev) e[p].rev = 0, psdrev(e[p].ls), psdrev(e[p].rs);}
void psdall(int p) {if(nrt(p)) psdall(e[p].fa);   psd(p);}
void rtt(int p) {
	int y = e[p].fa, z = e[y].fa, k = idy(p), s = e[p].ch[k^1];
	e[p].fa = z; if(nrt(y)) e[z].ch[idy(y)] = p;
	e[y].fa = p; e[p].ch[k^1] = y;
	e[s].fa = y; e[y].ch[k] = s;
}
void splay(int p) {
	psdall(p);
	for(int y = e[p].fa; nrt(p); rtt(p), y = e[p].fa)
		if(nrt(y)) rtt(idy(p) == idy(y) ? y : p);
}
void access(int p) {for(int y = 0; p; y = p, p = e[y].fa = getup(e[p].fa)) splay(p), e[p].rs = y;}
void mkrt(int p) {access(p); splay(p); psdrev(p);}
void split(int x, int y) {mkrt(x); access(y); splay(y);}
void link(int x, int y) {mkrt(x); e[x].fa = y;}
void dfs(int p, int rt) {
	if(!p) return;
	dfs(e[p].ls, rt); dfs(e[p].rs, rt);
	sz[rt] += sz[p]; upto[p] = rt;
}
void merge(int x, int y) {
	x = getup(x), y = getup(y);
	if(x == y) return;
	if(getup2(x) != getup2(y)) {link(x, y); upto2[getup2(x)] = getup2(y); return;}
	mkrt(x); access(y); splay(x);
	dfs(e[x].rs, x); e[x].rs = 0;
}

int main() {
	n = read(), m = read(); q = read();
	for(int i = 1; i <= n; i++) upto[i] = upto2[i] = i, sz[i] = 1, e[i] = (Node){{0, 0}, 0, 0};
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read();
		merge(u, v);
	}
	for(int i = 1; i <= q; i++) {
		int u = read(), v = read();
		merge(u, v);
		if(getup(u) == getup(v)) {
			printf("%d\n", sz[getup(u)]);
		} else printf("No\n");
	}
	return 0;
}
