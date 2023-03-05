#include<cstdio>
#include<cstring>
#include<cstdlib>
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
const int MAXN = 5e5 + 5;
namespace Treap {
	const int MAXNODE = MAXN * 50;
	struct Node {int ls, rs, v, s, k;}e[MAXNODE];
	int tot;
	int crenode(int v) {
		e[++tot] = (Node){0, 0, v, 1, rand()};
		return tot;
	}
	void upd(int x) {e[x].s = e[e[x].ls].s + e[e[x].rs].s + 1;}
	void split(int p, int& x, int& y, int v) {
		if(!p) {x = y = 0; return;}
		if(e[p].v <= v) {
			x = ++tot; e[x] = e[p]; split(e[p].rs, e[x].rs, y, v); upd(x);
		} else {
			y = ++tot; e[y] = e[p]; split(e[p].ls, x, e[y].ls, v); upd(y);
		}
	}
	int merge(int x, int y) {
		if(!x || !y) return x + y;
		int p = ++tot;
		if(e[x].k <= e[y].k) {
			e[p] = e[x]; e[p].rs = merge(e[x].rs, y); upd(p); return p;
		} else {
			e[p] = e[y]; e[p].ls = merge(x, e[y].ls); upd(p); return p;
		}
	}
	void ins(int& p, int v) {
		int x, y;
		split(p, x, y, v);
		p = merge(merge(x, crenode(v)), y);
	}
	void del(int& p, int v) {
		int x, y, z;
		split(p, x, y, v-1); split(y, y, z, v);
		p = merge(x, merge(merge(e[y].ls, e[y].rs), z));
	}
	int rk(int& p, int v) {
		int x, y, ans;
		split(p, x, y, v-1);
		ans = e[x].s + 1;
		p = merge(x, y);
		return ans;
	}
	int kth(int& p, int k) {
		if(k <= e[e[p].ls].s) return kth(e[p].ls, k);
		else if(k <= e[e[p].ls].s + 1) return p;
		else return kth(e[p].rs, k - e[e[p].ls].s - 1);
	}
	int pre(int& p, int v) {
		int x, y, ans;
		split(p, x, y, v-1);
		if(!x) ans = -2147483647;
		else ans = e[kth(x, e[x].s)].v;
		p = merge(x, y);
		return ans;
	}
	int nxt(int& p, int v) {
		int x, y, ans;
		split(p, x, y, v);
		if(!y) ans = 2147483647;
		else ans = e[kth(y, 1)].v;
		p = merge(x, y);
		return ans;
	}
}
using namespace Treap;
int rt[MAXN], n;
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		int v = read(), opt = read(), x = read();
		rt[i] = rt[v];
		if(opt == 1) ins(rt[i], x);
		else if(opt == 2) del(rt[i], x);
		else if(opt == 3) printf("%d\n", rk(rt[i], x));
		else if(opt == 4) printf("%d\n", e[kth(rt[i], x)].v);
		else if(opt == 5) printf("%d\n", pre(rt[i], x));
		else printf("%d\n", nxt(rt[i], x));
	}
	return 0;
}
