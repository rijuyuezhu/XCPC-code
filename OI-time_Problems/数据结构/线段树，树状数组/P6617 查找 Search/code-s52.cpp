#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
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
typedef set<int> SET;
const int MAXN = 5e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m, w, lans, f[MAXN], num[MAXN];
namespace Segtree {
#define ls o << 1
#define rs o << 1 | 1
	int val[MAXN << 2];
	void pushup(int o) {val[o] = min(val[ls], val[rs]);}
	void build(int o, int l, int r, int f[]) {
		if(l == r) {val[o] = f[l]; return ;}
		int m = (l + r) >> 1;
		build(ls, l, m, f); build(rs, m+1, r, f);
		pushup(o);
	}
	void mdypos(int o, int l, int r, int x, int v) {
		if(l == r) {val[o] = v; return ;}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(ls, l, m, x, v);
		else mdypos(rs, m+1, r, x, v);
		pushup(o);
	}
	int query(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y) return val[o];
		int m = (l + r) >> 1;
		if(y <= m) return query(ls, l, m, x, y);
		else if(x > m) return query(rs, m+1, r, x, y);
		else return min(query(ls, l, m, x, y), query(rs, m+1, r, x, y));
	}
#undef ls
#undef rs
}
using namespace Segtree;
namespace Settree {
	SET s[MAXN];
	int a[MAXN];
	void ins(int v, int i) {
		s[v].insert(i);
	}
	void del(int v, int i) {
		s[v].erase(i);
	}
	void init() {
		for(int i = 1; i <= n; i++)
			ins(a[i], i);
	}
	void mdy(int i, int v) {
		del(a[i], i);
		a[i] = v;
		ins(a[i], i);
	}
	int pre1(int i) {//sameval
		SET::iterator it = s[a[i]].lower_bound(i);
		if(it == s[a[i]].begin()) return INF;
		return *--it;
	}
	int nxt1(int i) {//sameval
		SET::iterator it = s[a[i]].upper_bound(i);
		if(it == s[a[i]].end()) return INF;
		return *it;
	}
	int pre2(int i) {//buval
		SET::iterator it = s[w-a[i]].lower_bound(i);
		if(it == s[w-a[i]].begin()) return INF;
		return *--it;
	}
	int nxt2(int i) {
		SET::iterator it = s[w-a[i]].upper_bound(i);
		if(it == s[w-a[i]].end()) return INF;
		return *it;
	}
}
using namespace Settree;
void gao1(int i, int v) {
	int p1 = pre1(i), p2 = pre2(i);
	if(p1 != INF) {
		if(p2 == INF || p2 <= p1)
			mdypos(1, 1, n, p1, query(1, 1, n, i, i));
	}
	if(p2 != INF) {
		if(p1 == INF || p1 <= p2)
			mdypos(1, 1, n, p2, nxt1(i));
	}
	mdy(i, v);
	p1 = pre1(i), p2 = pre2(i);
	if(p1 != INF) {
		if(p2 == INF || p2 <= p1)
			mdypos(1, 1, n, p1, INF);
	}
	if(p2 != INF) {
		if(p1 == INF || p1 <= p2)
			mdypos(1, 1, n, p2, i);
	}
	int n1 = nxt1(i), n2 = nxt2(i);
	if(n2 == INF) mdypos(1, 1, n, i, INF);
	else {
		if(n2 <= n1) mdypos(1, 1, n, i, n2);
		else mdypos(1, 1, n, i, INF);
	}

}
bool gao2(int l, int r) {
	return query(1, 1, n, l, r) <= r;
}
int main() {
	n = read(), m = read(), w = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	init();
	for(int i = n; i >= 1; i--) {
		if(num[w-a[i]]) {
			if(num[a[i]] > num[w-a[i]]) f[i] = num[w-a[i]];
			else f[i] = INF;
		} else f[i] = INF;
		num[a[i]] = i;
	}
	build(1, 1, n, f);
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read(), y = read();
		if(opt == 1) {
			gao1(x, y);
		} else {
			if(gao2(x ^ lans, y ^ lans)) {
				printf("Yes\n");
				lans++;
			} else {
				printf("No\n");
			}
		}
	}

	return 0;	
}
