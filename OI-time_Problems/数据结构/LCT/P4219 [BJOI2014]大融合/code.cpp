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
char readc() {
	char c = getchar();
	for(; c != 'A' && c != 'Q'; c = getchar());
	return c;
}
#define ls ch[0]
#define rs ch[1]

const int MAXN = 1e5 + 5;
int n, q;
struct Node {int fa, ch[2], sz, rev, szv;}e[MAXN];
int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
int idy(int p) {return e[e[p].fa].rs == p;}
void upd(int p) {e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz + 1 + e[p].szv;}
void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
void psd(int p) {if(e[p].rev) psdrev(e[p].ls), psdrev(e[p].rs), e[p].rev = 0;}
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
void access(int p) {for(int y = 0; p; y = p, p = e[p].fa) splay(p), e[p].szv += e[e[p].rs].sz, e[p].rs = y, e[p].szv -= e[e[p].rs].sz, upd(p);}
void mkrt(int p) {access(p); splay(p); psdrev(p);}
void split(int x, int y) {mkrt(x); access(y); splay(y);}
void link(int x, int y) {mkrt(x); access(y); splay(y); e[x].fa = y; e[y].szv += e[x].sz; upd(y);}


int main() {
	n = read(), q = read();
	for(int i = 1; i <= n; i++) e[i] = (Node){0, {0, 0}, 1, 0, 0};
	for(int i = 1; i <= q; i++) {
		char c = readc();
		if(c == 'A') {
			int x = read(), y = read();
			link(x, y);
		} else {
			int x = read(), y = read();
			split(x, y);
			printf("%lld\n", 1ll * (e[x].szv+1) * (e[y].szv+1));
		}
	}
	return 0;
}
