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
	struct Node{int fa, ch[2], sz;}e[MAXN];
	void upd(int x) {e[x].sz = e[e[x].ls].sz + e[e[x].rs].sz + 1;}
	int idy(int x) {return e[e[x].fa].rs == x;}
	int nrt(int x) {return e[e[x].fa].ls == x || e[e[x].fa].rs == x;}
	void rtt(int x) {
		int y = e[x].fa, z = e[y].fa, k = idy(x), s = e[x].ch[k^1];
		e[x].fa = z; if(nrt(y)) e[z].ch[idy(y)] = x;
		e[y].fa = x; e[x].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
		upd(y); upd(x);
	}
	void splay(int x) {
		for(int y = e[x].fa; nrt(x); rtt(x), y = e[x].fa)
			if(nrt(y)) rtt(idy(x) == idy(y) ? y : x);
	}
	void access(int x) {for(int y = 0; x; y = x, x = e[x].fa) splay(x), e[x].rs = y, upd(x);}
}
using namespace LCT;
void frsh(int x, int val) {
	if(k[x] && x + k[x] <= n) {
		access(x); splay(x);
		e[e[x].ls].fa = 0; e[x].ls = 0; upd(x);
	}
	k[x] = val;
	if(k[x] && x + k[x] <= n) {
		int y = x + k[x];
		access(x); splay(x); e[x].fa = y;
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) frsh(i, read());
	m = read();
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read() + 1;
		if(opt == 1) {
			access(x); splay(x); printf("%d\n", e[x].sz);
		} else frsh(x, read());
	}

	return 0;
}
