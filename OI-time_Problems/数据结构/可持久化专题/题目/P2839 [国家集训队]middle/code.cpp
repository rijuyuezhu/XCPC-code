#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int MAXN = 20005;
int n, q, a[MAXN], lsh[MAXN], tot, rt[MAXN], lans, dat[4];
vector<int> rg[MAXN];

void LSH() {
	sort(lsh + 1, lsh + 1 + tot);
	tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
namespace Sgt {
	struct SgtNode{int lv, rv, sv, ls, rs;}e[MAXN << 5];
	int tot, limtot;
	void upd(SgtNode& p, SgtNode a, SgtNode b) {
		p.sv = a.sv + b.sv;
		p.lv = max(a.lv, a.sv + b.lv);
		p.rv = max(b.rv, a.rv + b.sv);
	}
	void apply(SgtNode& p, int k) {p.lv = p.rv = p.sv = k;}
	void build(int& o, int l, int r) {
		o = ++tot;
		if(l == r) {apply(e[o], 1); return;}
		int m = (l + r) >> 1;
		build(e[o].ls, l, m); build(e[o].rs, m+1, r);
		upd(e[o], e[e[o].ls], e[e[o].rs]);
	}
	void mdypos(int& o, int pre, int l, int r, int x, int k) {
		if(pre <= limtot) {o = ++tot; e[o] = e[pre];}
		else o = pre;
		if(l == r) {apply(e[o], k); return ;}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(e[o].ls, e[pre].ls, l, m, x, k);
		else mdypos(e[o].rs, e[pre].rs, m+1, r, x, k);
		upd(e[o], e[e[o].ls], e[e[o].rs]);
	}
	SgtNode qryrange(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[o];
		int m = (l + r) >> 1;
		if(y <= m) return qryrange(e[o].ls, l, m, x, y);
		else if(x > m) return qryrange(e[o].rs, m+1, r, x, y);
		else {
			SgtNode ans; upd(ans, qryrange(e[o].ls, l, m, x, m), qryrange(e[o].rs, m+1, r, m+1, y));
			return ans;
		}
	}
}


void sol(int a, int b, int c, int d) {
	int l = 1, r = tot; lans = 0;
	while(l <= r) {
		int x = (l + r) >> 1;
		int cnt = 0;
		if(b+1 <= c-1) cnt += Sgt::qryrange(rt[x], 1, n, b+1, c-1).sv;
		cnt += Sgt::qryrange(rt[x], 1, n, a, b).rv;
		cnt += Sgt::qryrange(rt[x], 1, n, c, d).lv;
		if(cnt >= 0) {lans = x; l = x + 1;}
		else r = x - 1;
	}
	lans = lsh[lans];
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = lsh[++tot] = read();
	LSH();
	for(int i = 1; i <= n; i++) a[i] = LSH(a[i]), rg[a[i]].push_back(i);
	Sgt::build(rt[1], 1, n);
	for(int i = 2; i <= tot; i++) {
		Sgt::limtot = Sgt::tot;
		rt[i] = rt[i-1];
		for(int j = 0; j < rg[i-1].size(); j++) {
			int pos = rg[i-1][j];
			Sgt::mdypos(rt[i], rt[i], 1, n, pos, -1);
		}
	}
	q = read();
	for(int i = 1; i <= q; i++) {
		for(int j = 0; j < 4; j++) dat[j] = (read() + lans) % n + 1;
		sort(dat, dat + 4);
		int a = dat[0], b = dat[1], c = dat[2], d = dat[3];
		sol(a, b, c, d);
		printf("%d\n", lans);
	}
	return 0;
}
