#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
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
const int MAXN = 1e5 + 5, inf = 0x3f3f3f3f;
namespace Treap {
	struct Node { int ls, rs, val, k, siz, cnt; } e[MAXN];
	int tot;
	void upd(int p) { e[p].siz = e[e[p].ls].siz + e[e[p].rs].siz + e[p].cnt; }
	void lturn(int& p) { int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(s); p = s; }
	void rturn(int& p) { int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(s); p = s; }
	namespace Opt {
		void ins(int& p, int v) {
			if(!p) e[p = ++tot] = (Node){ 0, 0, v, rand(), 1, 1 };
			else if(e[p].val == v) e[p].cnt++, upd(p);
			else if(e[p].val > v) 
				ins(e[p].ls, v), e[e[p].ls].k < e[p].k ? rturn(p) : upd(p);
			else
				ins(e[p].rs, v), e[e[p].rs].k < e[p].k ? lturn(p) : upd(p);
		}
		void del(int& p, int v) {
			if(!p) return;
			else if(e[p].val > v) del(e[p].ls, v), upd(p);
			else if(e[p].val < v) del(e[p].rs, v), upd(p);
			else if(e[p].cnt > 1) --e[p].cnt, upd(p);
			else if(!e[p].ls) p = e[p].rs;
			else if(!e[p].rs) p = e[p].ls;
			else if(e[e[p].ls].k < e[e[p].rs].k)
				rturn(p), del(e[p].rs, v), upd(p);
			else
				lturn(p), del(e[p].ls, v), upd(p);
		}
		int rk(int p, int v) {
			if(!p) return 1;
			else if(e[p].val == v) return e[e[p].ls].siz + 1;
			else if(e[p].val > v) return rk(e[p].ls, v);
			else return e[e[p].ls].siz + e[p].cnt + rk(e[p].rs, v);
		}
		int kth(int p, int k) {
			if(!p) return inf;
			else if(k <= e[e[p].ls].siz) return kth(e[p].ls, k);
			else if(k <= e[e[p].ls].siz + e[p].cnt) return e[p].val;
			else return kth(e[p].rs, k - e[e[p].ls].siz - e[p].cnt);
		}
		int pre(int p, int v) {
			if(!p) return -inf;
			else if(e[p].val < v) return max(e[p].val, pre(e[p].rs, v));
			else return pre(e[p].ls, v);
		}
		int nxt(int p, int v) {
			if(!p) return inf;
			else if(e[p].val > v) return min(e[p].val, nxt(e[p].ls, v));
			else return nxt(e[p].rs, v);
		}
	}
}
using namespace Treap::Opt;
int n, rt;
int main() {
	srand(time(0));
	n = read();
	for(int i = 1; i <= n; i++) {
		int opt = read(), x = read();
		if(opt == 1) ins(rt, x);
		else if(opt == 2) del(rt, x);
		else if(opt == 3) printf("%d\n", rk(rt, x));
		else if(opt == 4) printf("%d\n", kth(rt, x));
		else if(opt == 5) printf("%d\n", pre(rt, x));
		else printf("%d\n", nxt(rt, x));
	}
	return 0;
}
