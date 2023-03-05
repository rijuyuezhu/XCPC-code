#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
int n, m, a[MAXN], seq[MAXN], pos[MAXN], del[MAXN];
ll ans[MAXN], nans;
namespace Treap {
	const int MAXNODE = MAXN << 5;
	struct Node{int ls, rs, v, c, s, k;}e[MAXNODE];
	int tot;
	void upd(int p) {e[p].s = e[e[p].ls].s + e[e[p].rs].s + e[p].c;}
	void lturn(int& p) {int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(s); p = s;}
	void rturn(int& p) {int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(s); p = s;}
	void ins(int& p, int v) {
		if(!p) e[p = ++tot] = (Node){0, 0, v, 1, 1, rand()};
		else if(e[p].v == v) e[p].c++, upd(p);
		else if(e[p].v > v)
			ins(e[p].ls, v), e[e[p].ls].k > e[p].k ? upd(p) : rturn(p);
		else 
			ins(e[p].rs, v), e[e[p].rs].k > e[p].k ? upd(p) : lturn(p);
	}
	ll le(int p, int v) {
		if(!p) return 0;
		else if(e[p].v == v) return e[e[p].ls].s + e[p].c;
		else if(e[p].v > v) return le(e[p].ls, v);
		else return e[e[p].ls].s + e[p].c + le(e[p].rs, v);
	}
}
namespace BIT {
	int rt[MAXN];
	int lowbit(int x) {return x&-x;}
	void ins(int x, int v) {
		for(int i = x; i <= n; i += lowbit(i)) Treap::ins(rt[i], v);
	}
	ll qry1(int x, int v) {//pos <= x && val <= v
		int ret = 0;
		for(int i = x; i; i -= lowbit(i)) ret += Treap::le(rt[i], v);
		return ret;
	}
	ll qry(int x, int v) {//(pos < x and val > v) or (pos > x and val < v) 
		return (qry1(x-1, n) - qry1(x-1, v)) + (qry1(n, v-1) - qry1(x, v-1));
	}
}		
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = read(), pos[a[i]] = i;
	for(int i = 1; i <= m; i++) seq[i] = pos[read()], del[seq[i]] = 1;
	for(int i = 1; i <= n; i++) if(!del[i]) {
		nans += BIT::qry(i, a[i]);
		BIT::ins(i, a[i]);
	}
	for(int i = m; i >= 1; i--) {
		nans += BIT::qry(seq[i], a[seq[i]]);
		BIT::ins(seq[i], a[seq[i]]);
		ans[i] = nans;
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
