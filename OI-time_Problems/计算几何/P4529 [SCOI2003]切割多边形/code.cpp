#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
#define fi first
#define se second
#define mp make_pair
const int MAXP = 20;
const db eps = 1e-8, inf = 1e10;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) : x(x), y(y) {}
};
typedef Pnt Vec;
typedef pair<Pnt, Pnt> Line;
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
db Len(const Vec& a) {return sqrt(Dot(a, a));}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
Pnt Crosspoint(const Pnt& u, const Pnt& v, const Pnt& p, const Pnt& q) {
	Vec uv = v-u, pq = q-p, pu = u-p;
	if(!dcmp(Cro(uv, pq))) return Pnt(inf, inf);
	return u + uv * (Cro(pq, pu) / Cro(uv, pq));
}
Pnt Crosspoint(const Line& a, const Line& b) {return Crosspoint(a.fi, a.se, b.fi, b.se);}

Pnt pi[MAXP];
Line a[MAXP];
int n, m, p, stk[MAXP], _stk;
bool used[MAXP];
db ans;
void dfs(int st, db ret) {
	if(dcmp(ret - ans) >= 0) return;
	if(st == p+1) {
		ans = ret;
		return ;
	}
	for(int i = 1; i <= p; i++) if(!used[i]) {
		Pnt ans1 = Pnt(inf, inf), ans2 = Pnt(inf, inf);
		for(int j = 1; j <= _stk; j++) {
			int k = stk[j];
			Pnt now = Crosspoint(a[k], a[i]);
			if(dcmp(Dot(a[i].se-a[i].fi, now-a[i].fi)) <= 0 && dcmp(Len(now-a[i].fi) - Len(ans1-a[i].fi)) < 0) ans1 = now;
			if(dcmp(Dot(a[i].fi-a[i].se, now-a[i].se)) <= 0 && dcmp(Len(now-a[i].se) - Len(ans2-a[i].se)) < 0) ans2 = now;
		}
		used[i] = 1; stk[++_stk] = i;
		dfs(st + 1, ret + Len(ans1-ans2));
		used[i] = 0; --_stk;
	}
}
int main() {
	n = read(), m = read();
	p = read();
	for(int i = 1; i <= p; i++) pi[i].x = read(), pi[i].y = read();
	for(int i = 1; i < p; i++) a[i] = mp(pi[i], pi[i+1]);
	a[p] = mp(pi[p], pi[1]);
	a[p+1] = mp(Pnt(0, 0), Pnt(0, m));
	a[p+2] = mp(Pnt(0, m), Pnt(n, m));
	a[p+3] = mp(Pnt(n, m), Pnt(n, 0));
	a[p+4] = mp(Pnt(n, 0), Pnt(0, 0));
	stk[++_stk] = p+1;
	stk[++_stk] = p+2;
	stk[++_stk] = p+3;
	stk[++_stk] = p+4;
	ans = inf;
	dfs(1, 0.0);
	printf("%.3lf\n", ans);
	return 0;
}
