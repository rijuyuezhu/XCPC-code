#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
const int MAXN = 5e4 + 5, MAXM = 2e5 + 5;
int n, q, m, a[MAXN], B, bel[MAXN], cl[MAXN], cr[MAXN];
ll ans[MAXN], nans;
struct Qry {
	int l, r, id;
}qry[MAXM];
bool cmp(const Qry& a, const Qry& b) {
	if(bel[a.l] != bel[b.l]) return bel[a.l] < bel[b.l];
	else if(bel[a.l] & 1) return a.r < b.r;
	else return a.r > b.r;
}
int Abs(int x) {return x < 0 ? -x : x;}
int Sgn(int x) {return x > 0 ? 1 : (x < 0 ? -1 : 0);}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	q = read();
	for(int i = 1; i <= q; i++) {
		int l1 = read(), r1 = read(), l2 = read(), r2 = read();
		qry[++m] = (Qry){r1, r2, i};
		qry[++m] = (Qry){l1-1, r2, -i};
		qry[++m] = (Qry){r1, l2-1, -i};
		qry[++m] = (Qry){l1-1, l2-1, i};
	}
	B = max(1, min(n, int(n / sqrt(m))));
	for(int i = 1; i <= n; i++) bel[i] = (i - 1) / B + 1;
	sort(qry + 1, qry + 1 + m, cmp);
	int l = 0, r = 0;
	for(int i = 1; i <= m; i++) {
		while(l < qry[i].l) {
			l++;
			nans += cr[a[l]];
			cl[a[l]]++;
		}
		while(l > qry[i].l) {
			nans -= cr[a[l]];
			cl[a[l]]--;
			l--;
		}
		while(r < qry[i].r) {
			r++;
			nans += cl[a[r]];
			cr[a[r]]++;
		}
		while(r > qry[i].r) {
			nans -= cl[a[r]];
			cr[a[r]]--;
			r--;
		}
		ans[Abs(qry[i].id)] += nans * Sgn(qry[i].id);
	}
	for(int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
	return 0;
}
