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
const int MAXM = 2e5 + 5;
int n, m;
namespace Segment_tree {
#define L e[o].ls
#define R e[o].rs
	struct Node {
		int ls, rs, fa, dep;
	}e[MAXN << 5];
	int tot;
	void build(int& o, int l, int r) {
		o = ++tot;
		if(l == r) {e[o] = (Node){0, 0, l, 1}; return ;}
		int m = (l + r) >> 1;
		build(L, l, m); build(R, m+1, r);
	}
	void mdypos(int& o, int pre, int l, int r, int x, int v) {//create a new version
		o = ++tot; e[o] = e[pre];
		if(l == r) {e[o].fa = v; return ;}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(L, e[pre].ls, l, m, x, v);
		else mdypos(R, e[pre].rs, m+1, r, x, v);
	}
	void adddep(int& o, int pre, int l, int r, int x) {
		o = ++tot; e[o] = e[pre];
		if(l == r) {e[o].dep++; return;}
		int m = (l + r) >> 1;
		if(x <= m) adddep(L, e[pre].ls, l, m, x);
		else adddep(R, e[pre].rs, m+1, r, x);
	}
	int findnode(int o, int l, int r, int x) {
		if(l == r) return o;
		int m = (l + r) >> 1;
		if(x <= m) return findnode(L, l, m, x);
		else return findnode(R, m+1, r, x);
	}
#undef L
#undef R
}
using namespace Segment_tree;
int getup(int v, int u) {
	int fo = findnode(v, 1, n, u);
	if(u == e[fo].fa) return fo;
	return getup(v, e[fo].fa);
}
	
int rt[MAXM];
int main() {
	n = read(), m = read();
	build(rt[0], 1, n);
	for(int i = 1; i <= m; i++) {
		int opt = read();
		if(opt == 1) {
			int u = read(), v = read();
			rt[i] = rt[i-1];
			int fu = getup(rt[i], u), fv = getup(rt[i], v);
			if(e[fu].fa == e[fv].fa) continue;
			if(e[fu].dep > e[fv].dep) swap(fu, fv);
			mdypos(rt[i], rt[i], 1, n, e[fu].fa, e[fv].fa);
			if(e[fu].dep == e[fv].dep) adddep(rt[i], rt[i], 1, n, e[fv].fa);
		} else if(opt == 2) {
			int k = read(); rt[i] = rt[k];
		} else {
			int u = read(), v = read();
			rt[i] = rt[i-1];
			int fu = getup(rt[i], u), fv = getup(rt[i], v);
			if(e[fu].fa == e[fv].fa) printf("1\n");
			else printf("0\n");
		}
	}
	return 0;
}
