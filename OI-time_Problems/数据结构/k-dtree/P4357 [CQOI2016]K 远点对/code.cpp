#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 100005;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct Pnt {
	int x, y;
	Pnt(int x = 0, int y = 0) :x(x), y(y) {}
};
bool cmpx(const Pnt& a, const Pnt& b) {return a.x < b.x;}
bool cmpy(const Pnt& a, const Pnt& b) {return a.y < b.y;}
priority_queue<ll, vector<ll>, greater<ll> > pq;
int n, k;
Pnt a[MAXN];
namespace KDTree {
	struct Node {
		int ls, rs, L, R, D, U, val;
	}e[MAXN];
	int tot, rt;
	bool (*Getd(int l, int r))(const Pnt&, const Pnt&) {
		double avx = 0, avy = 0, vax = 0, vay = 0;
		for(int i = l; i <= r; i++) avx += a[i].x, avy += a[i].y;
		avx /= (r-l+1); avy /= (r-l+1);
		for(int i = l; i <= r; i++)
			vax += 1ll * (a[i].x - avx) * (a[i].x - avx),
			vay += 1ll * (a[i].y - avy) * (a[i].y - avy);
		return vax > vay ? cmpx : cmpy;
	}
	void upd(int p) {
		e[p].L = e[p].R = a[e[p].val].x;
		e[p].U = e[p].D = a[e[p].val].y;
		if(e[p].ls) {
			e[p].L = min(e[p].L, e[e[p].ls].L);
			e[p].R = max(e[p].R, e[e[p].ls].R);
			e[p].D = min(e[p].D, e[e[p].ls].D);
			e[p].U = max(e[p].U, e[e[p].ls].U);
		} 
		if(e[p].rs) {
			e[p].L = min(e[p].L, e[e[p].rs].L);
			e[p].R = max(e[p].R, e[e[p].rs].R);
			e[p].D = min(e[p].D, e[e[p].rs].D);
			e[p].U = max(e[p].U, e[e[p].rs].U);
		} 
	}
	void build(int& p, int l, int r) {
		if(l > r) {p = 0; return;}
		int m = (l + r) >> 1;
		p = ++tot;
		nth_element(a + l, a + m, a + r + 1, Getd(l, r));
		e[p].val = m;
		build(e[p].ls, l, m-1); build(e[p].rs, m+1, r);
		upd(p);
	}
	ll sqr(ll x) {return x * x;}
	ll dist(Pnt a, Pnt b) {return sqr(a.x - b.x) + sqr(a.y - b.y);}
	ll distto(int p, Pnt v) {return max(sqr(v.x - e[p].L), sqr(v.x - e[p].R)) + max(sqr(v.y - e[p].D), sqr(v.y - e[p].U));}
	void query(int p, Pnt v) {
		if(!p) return;
		ll d = dist(a[e[p].val], v);
		if(d > pq.top()) pq.pop(), pq.push(d);
		ll distl = e[p].ls ? distto(e[p].ls, v) : -INF;
		ll distr = e[p].rs ? distto(e[p].rs, v) : -INF;
		if(distl > distr) {
			if(distl > pq.top()) query(e[p].ls, v);
			if(distr > pq.top()) query(e[p].rs, v);
		} else {
			if(distr > pq.top()) query(e[p].rs, v);
			if(distl > pq.top()) query(e[p].ls, v);
		}
	}
} using namespace KDTree;
int main() {
	n = read(); k = read(); k *= 2;
	for(int i = 1; i <= k; i++) pq.push(0);
	for(int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read();
	build(rt, 1, n);
	for(int i = 1; i <= n; i++) query(rt, a[i]);
	printf("%lld\n", pq.top());
	return 0;
}
