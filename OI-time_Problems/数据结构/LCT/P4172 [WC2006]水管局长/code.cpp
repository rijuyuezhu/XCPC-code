#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
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
const int MAXN = 1e3 + 5, MAXM = 2e5 + 5, MAXQ = 1e5 + 5, INF = 0x3f3f3f3f;

int n, m, q, dty[MAXM], upto[MAXN], bl[MAXM], val[MAXM], ans[MAXQ];
map<pii, int> rec;
struct Edge {int u, v, w;}ed[MAXM];
struct Qry {int op, u, v;}qry[MAXQ];

bool cmp(int A, int B) {return ed[A].w < ed[B].w;}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}

#define ls ch[0]
#define rs ch[1]
struct Node {int ch[2], fa, rev, mx;}e[MAXM];
int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
int idy(int p) {return e[e[p].fa].rs == p;}
void upd(int p) {
	e[p].mx = p;
	if(val[e[e[p].ls].mx] > val[e[p].mx]) e[p].mx = e[e[p].ls].mx;
	if(val[e[e[p].rs].mx] > val[e[p].mx]) e[p].mx = e[e[p].rs].mx;
}
void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
void psd(int p) {if(e[p].rev) e[p].rev = 0, psdrev(e[p].ls), psdrev(e[p].rs);}
void psdall(int p) {if(nrt(p)) psdall(e[p].fa); psd(p);}
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
void access(int p) {for(int y = 0; p; y = p, p = e[p].fa) splay(p), e[p].rs = y, upd(p);}
void mkrt(int p) {access(p); splay(p); psdrev(p);}
void split(int x, int y) {mkrt(x); access(y); splay(y);}
void link(int x, int y) {mkrt(x); e[x].fa = y;}
void cut(int x, int y) {split(x, y); e[y].ls = e[x].fa = 0; upd(y);}


int main() {
	n = read(); m = read(); q = read();
	for(int i = 1; i <= n; i++) upto[i] = i;
	for(int i = 1; i <= n+m; i++) e[i] = (Node){{0, 0}, 0, 0, i};
	val[0] = -INF;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), t = read();
		bl[i] = i; val[i+n] = t;
		ed[i] = (Edge){u, v, t};
		rec[pii(u, v)] = i; rec[pii(v, u)] = i;
	}
	for(int i = 1; i <= q; i++) {
		qry[i].op = read(); qry[i].u = read(); qry[i].v = read();
		if(qry[i].op == 2) dty[rec[pii(qry[i].u, qry[i].v)]] = 1;
	}
	sort(bl + 1, bl + 1 + m, cmp);
	int num = 0;
	for(int i = 1; i <= m && num < n-1; i++) if(!dty[bl[i]]) {
		int k = bl[i];
		int fu = getup(ed[k].u), fv = getup(ed[k].v);
		if(fu == fv) continue;
		num++;
		link(k+n, ed[k].u); link(k+n, ed[k].v);
		upto[fu] = fv;
	}
	for(int i = q; i >= 1; i--) {
		int u = qry[i].u, v = qry[i].v;
		if(qry[i].op == 1) {
			split(u, v);
			ans[i] = val[e[v].mx];
		} else {
			split(u, v); int t = e[v].mx, k = rec[pii(qry[i].u, qry[i].v)] + n;
			if(val[t] > val[k]) {
				cut(t, ed[t-n].u); cut(t, ed[t-n].v);
				link(k, ed[k-n].u); link(k, ed[k-n].v);
			}
		}
	}
	for(int i = 1; i <= q; i++) if(qry[i].op == 1) printf("%d\n", ans[i]);
	return 0;
}
