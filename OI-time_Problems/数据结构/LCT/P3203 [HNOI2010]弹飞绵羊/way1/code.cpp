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
int n, m, k[MAXN];
namespace LCT {
	#define ls ch[0]
	#define rs ch[1]
	struct LCTNode{int fa, ch[2], rev, sz;}e[MAXN];
	int nrt(int x) {return e[e[x].fa].ls == x || e[e[x].fa].rs == x;}
	int idy(int x) {return e[e[x].fa].rs == x;}
	void upd(int x) {e[x].sz = e[e[x].ls].sz + e[e[x].rs].sz + 1;}
	void psdrev(int x) {if(x) e[x].rev ^= 1, swap(e[x].ls, e[x].rs);}
	void psd(int x) {if(e[x].rev) e[x].rev = 0, psdrev(e[x].ls), psdrev(e[x].rs);}
	void psdall(int x) {if(nrt(x)) psdall(e[x].fa); psd(x);}
	void rtt(int x) {
		int y = e[x].fa, z = e[y].fa, k = idy(x), s = e[x].ch[k^1];
		e[x].fa = z; if(nrt(y)) e[z].ch[idy(y)] = x;
		e[s].fa = y; e[y].ch[k] = s;
		e[y].fa = x; e[x].ch[k^1] = y;
		upd(y); upd(x);
	}
	void splay(int x) {
		psdall(x);
		for(int y = e[x].fa; nrt(x); rtt(x), y = e[x].fa)
			if(nrt(y)) rtt(idy(x) == idy(y) ? y : x);
	}
	void access(int x) {for(int y = 0; x; y = x, x = e[x].fa) splay(x), e[x].rs = y, upd(x);}
	void mkrt(int x) {access(x); splay(x); psdrev(x);}
	void split(int x, int y) {mkrt(x); access(y); splay(y);}
	void link(int x, int y) {mkrt(x); e[x].fa = y;}
	void cut(int x, int y) {split(x, y); e[x].fa = e[y].ls = 0; upd(y);}
}
using namespace LCT;

void frsh(int u, int val) {
	if(k[u]) {
		int v = min(u + k[u], n+1);
		cut(u, v);
	}
	k[u] = val;
	if(k[u]) {
		int v = min(u + k[u], n+1);
		link(u, v);
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) frsh(i, read());
	m = read();
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read()+1;
		if(opt == 1) {
			split(x, n+1);
			printf("%d\n", e[n+1].sz - 1);
		} else frsh(x, read());
	}
	return 0;
}
