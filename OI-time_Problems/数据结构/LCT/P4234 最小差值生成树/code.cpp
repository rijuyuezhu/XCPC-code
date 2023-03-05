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
const int MAXN = 5e4 + 5;
const int INF = 0x3f3f3f3f;
const int MAXM = 2.5e5 + 5;
int n, m, val[MAXM], upto[MAXN], del[MAXM];
struct Edge {int u, v, w;}ed[MAXM];
bool cmp(const Edge& A, const Edge& B) {return A.w < B.w;}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}

#define ls ch[0]
#define rs ch[1]
struct Node {int ch[2], fa, rev, mn;}e[MAXM];
int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
int idy(int p) {return e[e[p].fa].rs == p;}
void upd(int p) {
	e[p].mn = p;
	if(val[e[e[p].ls].mn] < val[e[p].mn]) e[p].mn = e[e[p].ls].mn;
	if(val[e[e[p].rs].mn] < val[e[p].mn]) e[p].mn = e[e[p].rs].mn;
}
void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
void psd(int p) {if(e[p].rev) e[p].rev = 0, psdrev(e[p].ls), psdrev(e[p].rs);}
void psdall(int p) {if(nrt(p)) psdall(e[p].fa);   psd(p);}
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
	n = read(); m = read();
	for(int i = 1; i <= m; i++) ed[i].u = read(), ed[i].v = read(), ed[i].w = read();
	for(int i = 1; i <= n; i++) upto[i] = i;
	for(int i = 1; i <= n+m; i++) e[i] = (Node){{0, 0}, 0, 0, i};
	for(int i = 0; i <= n; i++) val[i] = INF;

	sort(ed + 1, ed + 1 + m, cmp);
	int num = 0, tow = 1, ans = INF;
	for(int i = 1; i <= m; i++) {
		int u = ed[i].u, v = ed[i].v;
		if(u == v) {del[i] = 1; continue;} //self circle
		val[i+n] = ed[i].w;
		if(getup(u) != getup(v)) {
			upto[getup(u)] = getup(v);
			num++;
			link(i+n, u); link(i+n, v);
		} else {
			split(u, v); int t = e[v].mn;
			del[t-n] = 1;
			cut(t, ed[t-n].u); cut(t, ed[t-n].v);
			link(i+n, u); link(i+n, v);
		}
		if(num == n-1) {
			while(del[tow]) tow++;
			ans = min(ans, ed[i].w - ed[tow].w);
		}
			
	}
	printf("%d\n", ans);
	return 0;
}
