#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e4 + 5;

#define ls ch[0]
#define rs ch[1]
struct Node {int ch[2], fa, rev;}e[MAXN];
int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
int idy(int p) {return e[e[p].fa].rs == p;}
void upd(int p) {}
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
int getrt(int p) {access(p); splay(p); while(e[p].ls) psd(p = e[p].ls); splay(p); return p;}
void split(int x, int y) {mkrt(x); access(y); splay(y);}
void link(int x, int y) {mkrt(x); e[x].fa = y;}
void cut(int x, int y) {split(x, y); e[y].ls = e[x].fa = 0; upd(y);}
int n, m;

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) e[i] = (Node){{0, 0}, 0, 0};
	for(int i = 1; i <= m; i++) {
		char s[10]; int u, v;
		scanf("%s", s); u = read(), v = read();
		if(s[0] == 'C') link(u, v);
		else if(s[0] == 'D') cut(u, v);
		else {
			mkrt(u);
			if(getrt(v) == u) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}
