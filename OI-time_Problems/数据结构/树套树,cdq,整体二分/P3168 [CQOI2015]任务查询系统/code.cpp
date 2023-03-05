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
typedef pair<int, int> pii;
const int MAXN = 2e5 + 5;
int m, n, rt[MAXN], lsh[MAXN], lsh_num;
struct Item {int l, r, c;}a[MAXN];
vector<pii> opt[MAXN];
ll lans;
namespace Sgt {
	struct Node{int ls, rs; ll sz, sum;}e[MAXN << 5];
	int limtot, tot;
	void setlim() {limtot = tot;}
	void mdypos(int& p, int pre, int l, int r, int x, int v) {
		if(pre <= limtot) p = ++tot, e[p] = e[pre];
		else p = pre;
		e[p].sz += v; e[p].sum += lsh[x] * v;
		if(l == r) return;
		int m = (l + r) >> 1;
		if(x <= m) mdypos(e[p].ls, e[pre].ls, l, m, x, v);
		else mdypos(e[p].rs, e[pre].rs, m+1, r, x, v);
	}
	ll qry(int p, int l, int r, int k) {
		if(l == r) return e[p].sz == 0 ? 0 : e[p].sum / e[p].sz * k;
		int m = (l + r) >> 1;
		if(k <= e[e[p].ls].sz) return qry(e[p].ls, l, m, k);
		else return e[e[p].ls].sum + qry(e[p].rs, m+1, r, k - e[e[p].ls].sz);
	}
}
using namespace Sgt;
void LSH() {
	sort(lsh + 1, lsh + 1 + lsh_num);
	lsh_num = unique(lsh + 1, lsh + 1 + lsh_num) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + lsh_num, x) - lsh;
}
int main() {
	m = read(); n = read();
	for(int i = 1; i <= m; i++) a[i].l = read(), a[i].r = read(), lsh[++lsh_num] = a[i].c = read();
	LSH();
	for(int i = 1; i <= m; i++) a[i].c = LSH(a[i].c);
	for(int i = 1; i <= m; i++) opt[a[i].l].push_back(pii(a[i].c, 1)), opt[a[i].r+1].push_back(pii(a[i].c, -1));
	for(int i = 1; i <= 1e5; i++) {
		Sgt::setlim();
		rt[i] = rt[i-1];
		for(int j = 0; j < (int)opt[i].size(); j++)
			Sgt::mdypos(rt[i], rt[i], 1, lsh_num, opt[i][j].first, opt[i][j].second);
	}
	lans = 1;
	for(int i = 1; i <= n; i++) {
		int x = read(), a = read(), b = read(), c = read();
		int k = 1 + (1ll * a * lans + b) % c;
		printf("%lld\n", lans = Sgt::qry(rt[x], 1, lsh_num, k));
	}
	return 0;
}
