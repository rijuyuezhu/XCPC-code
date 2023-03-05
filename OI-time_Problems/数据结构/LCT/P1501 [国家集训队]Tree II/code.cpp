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
	char ch = getchar();
	for(; ch != '+' && ch != '-' && ch != '*' && ch != '/'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
const int P = 51061;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int n, q;
namespace LCT {
	#define ls ch[0]
	#define rs ch[1]
	struct Node{
		int ch[2], fa, lm, la, v, sv, sz, rev;
	}e[MAXN];
	int idy(int x) {return e[e[x].fa].rs == x;}
	int nrt(int x) {return e[e[x].fa].ls == x || e[e[x].fa].rs == x;}
	void upd(int x) {
		e[x].sv = pls(e[x].v, pls(e[e[x].ls].sv, e[e[x].rs].sv));
		e[x].sz = 1 + e[e[x].ls].sz + e[e[x].rs].sz;
	}
	void psdrev(int x) {
		if(x) swap(e[x].ls, e[x].rs), e[x].rev ^= 1;
	}
	void psdmul(int x, int k) {
		if(x) {
			e[x].lm = mul(e[x].lm, k); 
			e[x].la = mul(e[x].la, k);
			e[x].v = mul(e[x].v, k);
			e[x].sv = mul(e[x].sv, k);
		}
	}
	void psdadd(int x, int k) {
		if(x) {
			e[x].la = pls(e[x].la, k);
			e[x].v = pls(e[x].v, k);
			e[x].sv = pls(e[x].sv, mul(k, e[x].sz));
		}
	}
	void psd(int x) {
		if(e[x].rev) {
			psdrev(e[x].ls); psdrev(e[x].rs);
			e[x].rev = 0;
		}
		if(e[x].lm != 1) {
			psdmul(e[x].ls, e[x].lm); psdmul(e[x].rs, e[x].lm);
			e[x].lm = 1;
		}
		if(e[x].la) {
			psdadd(e[x].ls, e[x].la); psdadd(e[x].rs, e[x].la);
			e[x].la = 0;
		}
	}
	void psdall(int x) {
		if(nrt(x)) psdall(e[x].fa);
		psd(x);
	}
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
	void split(int x, int y) {mkrt(x); access(y); splay(y);}
	void link(int x, int y) {mkrt(x); e[x].fa = y;}
	void cut(int x, int y) {split(x, y); e[x].fa = e[y].ls = 0; upd(y);}
	
}
using namespace LCT;

int main() {
	n = read(); q = read();
	for(int i = 1; i <= n; i++)
		e[i] = (Node){{0, 0}, 0, 1, 0, 1, 1, 1, 0};
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		link(u, v);
	}
	for(int i = 1; i <= q; i++) {
		char opt = readc();
		int u = read(), v = read();
		if(opt == '+') {
			split(u, v); psdadd(v, read());
		} else if(opt == '-') {
			cut(u, v);
			u = read(), v = read();
			link(u, v);
		} else if(opt == '*') {
			split(u, v); psdmul(v, read());
		} else {
			split(u, v);
			printf("%d\n", e[v].sv);
		}
	}
	return 0;
}
