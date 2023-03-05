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
namespace Segment_tree {
	#define L e[o].ls
	#define R e[o].rs
	const int MAXNODE = MAXN << 5;
	struct Node {
		int ls, rs, num;
	}e[MAXNODE];
	int tot, rt[MAXN];
	void pushup(int o) {
		e[o].num = e[L].num + e[R].num;
	}
	void build(int& o, int l, int r) {
		o = ++tot;
		if(l == r) return ;
		int m = (l + r) >> 1;
		build(L, l, m); build(R, m+1, r);
	}
	void update(int& o, int pre, int l, int r, int x) {
		o = ++tot; e[o] = e[pre];
		if(l == r) {e[o].num++; return ;}
		int m = (l + r) >> 1;
		if(x <= m) update(L, e[pre].ls, l, m, x);
		else update(R, e[pre].rs, m+1, r, x);
		pushup(o);
	}
	int query(int u, int v, int l, int r, int k) {
		if(l == r) return l;
		int m = (l + r) >> 1;
		if(k <= e[e[v].ls].num - e[e[u].ls].num) return query(e[u].ls, e[v].ls, l, m, k);
		else return query(e[u].rs, e[v].rs, m+1, r, k - (e[e[v].ls].num - e[e[u].ls].num));
	}
	#undef L
	#undef R
}
using namespace Segment_tree;
int n, m;
int a[MAXN];
int lsh[MAXN], idx;
void LSH() {
	sort(lsh + 1, lsh + 1 + idx);
	idx = unique(lsh + 1, lsh + 1 + idx) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + idx, x) - lsh;
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = lsh[++idx] = read();
	LSH();
	build(rt[0], 1, idx);
	for(int i = 1; i <= n; i++) update(rt[i], rt[i-1], 1, idx, LSH(a[i]));
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read(), k = read();
		printf("%d\n", lsh[query(rt[l-1], rt[r], 1, idx, k)]);
	}

	return 0;
}
