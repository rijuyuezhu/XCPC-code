#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5, INF = 0x3f3f3f3f;
namespace Splay { 
#define ls ch[0]
#define rs ch[1]
	struct Node {int ch[2], fa, val, siz, rev;} e[MAXN];
	int tot, rt;
	void upd(int p) {e[p].siz = e[e[p].ls].siz + e[e[p].rs].siz + 1;}
	int idy(int p) {return e[e[p].fa].rs == p;}
	void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
	void psd(int p) {if(e[p].rev) e[p].rev = 0, psdrev(e[p].ls), psdrev(e[p].rs);}
	void rtt(int p) {
		int y = e[p].fa, z = e[y].fa, k = idy(p), s = e[p].ch[k^1];
		e[p].fa = z; e[z].ch[idy(y)] = p;
		e[s].fa = y; e[y].ch[k] = s;
		e[y].fa = p; e[p].ch[k^1] = y;
		upd(y); upd(p);
	}
	void splay(int p, int to) {
		for(int y = e[p].fa; e[p].fa != to; rtt(p), y = e[p].fa)
			if(e[y].fa != to) rtt(idy(p) == idy(y) ? y : p);
		if(!to) rt = p;
	}
	void build(int& p, int l, int r, int a[], int fa) {
		if(l > r) {p = 0; return ;}
		int m = (l + r) >> 1;
		e[p = ++tot] = (Node){{0, 0}, fa, a[m], 1, 0};
		build(e[p].ls, l, m-1, a, p);
		build(e[p].rs, m+1, r, a, p);
		upd(p);
	}
	int kth(int k) {
		k++;
		int p = rt;
		while(p) {
			psd(p);
			if(k <= e[e[p].ls].siz) p = e[p].ls;
			else if(k <= e[e[p].ls].siz + 1) return p;
			else {k -= e[e[p].ls].siz + 1; p = e[p].rs;}
		}
		return -1;
	}
	void rev(int l, int r) {
		int L = kth(l-1), R = kth(r+1);
		splay(L, 0); splay(R, L);
		int p = e[R].ls;
		psdrev(p);
	}
	void print(int p) {
		if(!p) return ;
		psd(p);
		print(e[p].ls);
		if(e[p].val != INF) printf("%d ", e[p].val);
		print(e[p].rs);
	}
#undef ls
#undef rs
} using namespace Splay;
int n, m, a[MAXN];
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = i;
	a[0] = INF, a[n+1] = INF;
	build(rt, 0, n+1, a, 0);
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read();
		rev(l, r);
	}
	print(rt);
	return 0;
}
