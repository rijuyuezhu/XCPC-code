#include <iostream>
#include <algorithm>
using namespace std;

constexpr int INF = 0x3f3f3f3f;
constexpr int MAXN = 5e5 + 5;
struct Que {
	int l, r, id;
	bool operator < (const Que &B)const
	{
		return l > B.l;
	}
};

int n, m, a[MAXN], discr[MAXN], _discr, before[MAXN];
int nxt[MAXN], ans[MAXN];
Que que[MAXN];

void get_discrete()
{
	sort(discr + 1, discr + 1 + _discr);
	_discr = unique(discr + 1, discr + 1 + _discr) - discr - 1;
}

int get_discrete(int x)
{
	return lower_bound(discr + 1, discr + 1 + _discr, x) - discr;
}

namespace seg_tree {
#define ls o << 1
#define rs o << 1 | 1

	int val[MAXN << 2];

	void pushup(int o)
	{
		val[o] = min(val[ls], val[rs]);
	}

	void build(int o, int l, int r)
	{
		val[o] = INF;
		if (l == r)
			return;
		int m = (l + r) >> 1;
		build(ls, l, m);
		build(rs, m+1, r);
		pushup(o);
	}

	void mdypoint(int o, int l, int r, int x, int v)
	{
		if (l == r) {
			val[o] = v;
			return;
		}
		int m = (l + r) >> 1;
		if (x <= m)
			mdypoint(ls, l, m, x, v);
		else
			mdypoint(rs, m+1, r, x, v);
		pushup(o);
	}

	int minrange(int o, int l, int r, int x, int y)
	{
		if (x <= l && r <= y)
			return val[o];
		int m = (l + r) >> 1;
		if (y <= m)
			return minrange(ls, l, m, x, y);
		else if (x > m)
			return minrange(rs, m+1, r, x, y);
		else
			return min(minrange(ls, l, m, x, m), minrange(rs, m+1, r, m+1, y));
	}


#undef ls
#undef rs
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		discr[++_discr] = a[i];
	}
	get_discrete();
	for (int i = 1; i <= n; i++)
		a[i] = get_discrete(a[i]);
	for (int i = 1; i <= m; i++) {
		cin >> que[i].l >> que[i].r;
		que[i].id = i;
	}
	sort(que + 1, que + 1 + m);

	for (int i = 1; i <= n; i++) {
		int x = before[a[i]];
		if (x) {
			nxt[x] = i;
		}
		before[a[i]] = i;
	}

	seg_tree::build(1, 1, n);
	int lst = n+1;
	for (int k = 1; k <= m; k++) {
		const Que &now = que[k];
		while (lst > now.l) {
			lst--;
			if (nxt[lst]) {
				seg_tree::mdypoint(1, 1, n, nxt[lst], nxt[lst] - lst);
			}
		}
		ans[now.id] = seg_tree::minrange(1, 1, n, now.l, now.r);
	}
	
	for (int i = 1; i <= m; i++)
		cout << (ans[i] == INF ? -1 : ans[i]) << '\n';

	return 0;
}
