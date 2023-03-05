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
	for(; ch != 'B' && ch != 'Q'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
int n, m, q, p[MAXN], fa[MAXN];


int getfa(int u) {return fa[u] == u ? u : fa[u] = getfa(fa[u]);}

namespace Segment_Tree {
#define L e[o].ls
#define R e[o].rs
	const int MAXNODE = 6e6 + 5;
	struct Node {
		int ls, rs;
		int sz, num;
	}e[MAXNODE];
	int tot;
	void pushup(int o) {e[o].sz = e[L].sz + e[R].sz;}
	void mdy(int& o, int l, int r, int x, int id) {
		if(!o) o = ++tot;
		if(l == r) {e[o].sz++; e[o].num = id; return ;}
		int m = (l + r) >> 1;
		if(x <= m) mdy(L, l, m, x, id);
		else mdy(R, m+1, r, x, id);
		pushup(o);
	}
	int merge(int u, int v, int l, int r) {//merge v to u(replace u)
		if(!u || !v) return u + v;
		if(l == r) { 
			if(e[v].num){
				e[u].sz += e[v].sz;
				e[u].num = e[v].num;//?
			}
			return u;
		}
		int m = (l + r) >> 1;
		e[u].ls = merge(e[u].ls, e[v].ls, l, m);
		e[u].rs = merge(e[u].rs, e[v].rs, m+1, r);
		pushup(u);
		return u;
	}
	int query(int o, int l, int r, int k) {
		if(!o || k > e[o].sz) return -1;
		if(l == r) return e[o].num;
		int m = (l + r) >> 1;
		if(k <= e[L].sz) return query(L, l, m, k);
		else return query(R, m+1, r, k - e[L].sz);
	}

#undef L
#undef R
}
using namespace Segment_Tree;

int rt[MAXN];
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) p[i] = read(), fa[i] = i, rt[i] = i;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read();
		fa[getfa(u)] = getfa(v);
	}
	for(int i = 1; i <= n; i++)
		mdy(rt[getfa(i)], 1, n, p[i], i);
	q = read();
	for(int i = 1; i <= q; i++) {
		char opt = readc();
		int x = read(), y = read();
		if(opt == 'Q') {
			printf("%d\n", query(rt[getfa(x)], 1, n, y));
		} else {
			int fx = getfa(x), fy = getfa(y);
			if(fx == fy) continue;
			fa[fx] = fy;
			rt[fy] = merge(rt[fy], rt[fx], 1, n);
		}
	}
	return 0;
}
