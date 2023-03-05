#include<cstdio>
#include<cstring>
#include<map>
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
typedef pair<int, int> pii;
const int MAXN = 3e4 + 5;
const int MAXM = 1e5 + 5;
const int MAXQ = 4e4 + 5;
struct Edge {int u, v;}ed[MAXM];
struct Qry {int op, u, v;}q[MAXQ];
map<pii, int> mp;
int n, m, dty[MAXM], q_num, upto[MAXN], ans[MAXQ];
int getup(int p) {return upto[p] == p ? p : upto[p] = getup(upto[p]);}
namespace LCT {
#define ls ch[0]
#define rs ch[1]
	struct Node {int ch[2], fa, rev, sz;}e[MAXN];
	int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
	int idy(int p) {return e[e[p].fa].rs == p;}
	void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
	void psd(int p) {if(e[p].rev) e[p].rev = 0, psdrev(e[p].ls), psdrev(e[p].rs);}
	void psdall(int p) {if(nrt(p)) psdall(e[p].fa); psd(p);}
	void upd(int p) {e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz + 1;}
	void rtt(int p) {
		int y = e[p].fa, z = e[y].fa, k = idy(p), s = e[p].ch[k^1];
		e[p].fa = z; if(nrt(y)) e[z].ch[idy(y)] = p;
		e[y].fa = p; e[p].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
		upd(y); upd(p);
	}
	void splay(int p) {
		psdall(p);
		for(int y = e[p].fa; nrt(p); rtt(p), y = e[p].fa)
			if(nrt(y)) rtt(idy(p) == idy(y) ? y : p);
	}
	void access(int p) {for(int y = 0; p; y = p, p = e[y].fa = getup(e[p].fa)) splay(p), e[p].rs = y, upd(p);}
	void mkrt(int p) {access(p); splay(p); psdrev(p);}
	int getrt(int p) {access(p); splay(p); while(e[p].ls) psd(p = e[p].ls); splay(p); return p;}
	void split(int x, int y) {mkrt(x); access(y); splay(y);}
}
using namespace LCT;
void dfs(int p, int rt) {
	if(!p) return ;
	dfs(e[p].ls, rt); dfs(e[p].rs, rt);
	upto[p] = rt;
}
void merge(int u, int v) {
	if(u == v) return ;
	mkrt(u);
	if(getrt(v) != u) {e[u].fa = v; return ;}
	dfs(e[u].rs, u);
	e[u].rs = 0; upd(u);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) upto[i] = i, e[i] = (Node){{0, 0}, 0, 0, 1};
	for(int i = 1; i <= m; i++) {
		ed[i].u = read(), ed[i].v = read();
		mp[pii(ed[i].u, ed[i].v)] = i; mp[pii(ed[i].v, ed[i].u)] = i;
	}
	while(1) {
		int id = read();
		if(id == -1) break;
		int u = read(), v = read();
		q[++q_num] = (Qry){id, u, v};
	}
	for(int i = 1; i <= q_num; i++) if(q[i].op == 0) dty[mp[pii(q[i].u, q[i].v)]] = 1;
	for(int i = 1; i <= m; i++) if(!dty[i]) merge(getup(ed[i].u), getup(ed[i].v));
	for(int i = q_num; i >= 1; i--) {
		int u = getup(q[i].u), v = getup(q[i].v);
		if(q[i].op == 0) {
			merge(u, v);
		} else {
			split(u, v);
			ans[i] = e[v].sz - 1;
		}
	}
	for(int i = 1; i <= q_num; i++)
		if(q[i].op == 1)
			printf("%d\n", ans[i]);
	return 0;
}
