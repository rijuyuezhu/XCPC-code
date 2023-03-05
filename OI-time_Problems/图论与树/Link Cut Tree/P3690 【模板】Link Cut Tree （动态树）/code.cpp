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
const int MAXN = 1e5 + 5;
int n, m, val[MAXN];
namespace LCT {
	#define ls ch[0]
	#define rs ch[1]
	struct Node {int ch[2], fa, rev, sum;}e[MAXN];
	int nrt(int x) {return e[e[x].fa].ls == x || e[e[x].fa].rs == x;}
	int idy(int x) {return e[e[x].fa].rs == x;}
	void upd(int x) {e[x].sum = e[e[x].ls].sum ^ e[e[x].rs].sum ^ val[x];}
	void psdrev(int x) {if(x) swap(e[x].ls, e[x].rs), e[x].rev ^= 1;}
	void psd(int x) {if(e[x].rev) e[x].rev = 0, psdrev(e[x].ls), psdrev(e[x].rs);}
	void psdall(int x) {if(nrt(x)) psdall(e[x].fa); psd(x);}
	void rtt(int x) {
		int y = e[x].fa, z = e[y].fa, k = idy(x), s = e[x].ch[k^1];
		e[x].fa = z; if(nrt(y)) e[z].ch[idy(y)] = x;
		e[y].fa = x; e[x].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
		upd(y); upd(x);
	}
	void splay(int x) {
		psdall(x);
		for(int y = e[x].fa; nrt(x); rtt(x), y = e[x].fa)
			if(nrt(y)) rtt(idy(x) == idy(y) ? y : x);
	}
	void access(int x) {for(int y = 0; x; y = x, x = e[x].fa) splay(x), e[x].rs = y, upd(x);}
	void mkrt(int x) {access(x); splay(x); psdrev(x);}
	int getrt(int x) {access(x); splay(x); while(e[x].ls) psd(x = e[x].ls); splay(x); return x;}
	void split(int x, int y) {mkrt(x); access(y); splay(y);}
	void link(int x, int y) {mkrt(x); if(getrt(y) != x) e[x].fa = y;}
	void cut(int x, int y) {mkrt(x); if(getrt(y) == x && e[y].fa == x && e[y].ls == 0) e[x].rs = e[y].fa = 0, upd(x);}
}
using namespace LCT;

int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) val[i] = read();
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read(), y = read();
		if(opt == 0) {split(x, y); printf("%d\n", e[y].sum);}
		else if(opt == 1) link(x, y);
		else if(opt == 2) cut(x, y);
		else {
			splay(x); val[x] = y; upd(x);
		}
	}
	return 0;
}
