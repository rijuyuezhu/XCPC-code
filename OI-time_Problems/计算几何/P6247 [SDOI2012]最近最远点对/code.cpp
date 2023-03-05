#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
typedef double db;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
const db eps = 1e-8, inf = 1e40;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
int dcmp(db x, db y) {return dcmp(x-y);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) : x(x), y(y) {}
}; typedef Pnt Vec;
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
bool operator < (const Vec& a, const Vec& b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
bool operator == (const Vec& a, const Vec& b) {return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
db Len2(const Vec& a) {return Dot(a, a);}
db Len(const Vec& a) {return sqrt(Len2(a));}
typedef vector<Pnt> Polygon;
Polygon ConvexHull(Polygon G) {
	static int st[MAXN];
	sort(G.begin(), G.end());
	unique(G.begin(), G.end());
	if((int)G.size() <= 2) return G;
	int n = G.size(), top = 0;
	st[++top] = 0; st[++top] = 1;
	for(int i = 2; i < n; i++) {
		while(top > 1 && dcmp(Cro(G[st[top]]-G[st[top-1]], G[i]-G[st[top]]) <= 0)) --top;
		st[++top] = i;
	}
	int t = top; st[++top] = n-2;
	for(int i = n-3; i >= 0; i--) {
		while(top > t && dcmp(Cro(G[st[top]]-G[st[top-1]], G[i]-G[st[top]]) <= 0)) --top;
		st[++top] = i;
	}
	Polygon T;
	for(int i = 1; i < top; i++) T.push_back(G[st[i]]);
	return T;
}
db Getmax(const Polygon& G) {
	int n = G.size();
	if(n == 1) return 0;
	else if(n == 2) return Len(G[0]-G[1]);
	else {
		db ans = Len(G[0]-G[1]);
		for(int i = 0, j = 2; i < n; i++) {
			int ip = i+1 == n ? 0 : i+1, j2 = j+1 == n ? 0 : j+1;
			while(Cro(G[ip]-G[i], G[j]-G[i]) < Cro(G[ip]-G[i], G[j2]-G[i])) j = j2, j2 = j2+1 == n ? 0 : j2+1;
			ans = max(ans, max(Len(G[j]-G[i]), Len(G[j]-G[ip])));
		}
		return ans;
	}
}
int n, _tmp;
Polygon G;
Pnt tmp[MAXN];
db Solve(int l, int r) {
	if(l == r) return inf;
	int m = (l + r) >> 1; db mid = G[m].x;
	db d = min(Solve(l, m), Solve(m+1, r));
	_tmp = 0;
	for(int i = l; i < r; i++)
		if(dcmp(G[i].x, mid - d) >= 0 && dcmp(G[i].x, mid + d) <= 0) tmp[++_tmp] = G[i];
	for(int i = 1; i <= _tmp; i++)
		for(int j = i+1; j <= _tmp; j++) {
			d = min(d, Len(tmp[j]-tmp[i]));
			if(dcmp(tmp[j].y - tmp[i].y, d) >= 0) break;
		}
	int p = l, q = m+1, k = l;
	while(p <= m && q <= r)
		if(G[p].y < G[q].y) tmp[k++] = G[p++];
		else tmp[k++] = G[q++];
	while(p <= m) tmp[k++] = G[p++];
	while(q <= r) tmp[k++] = G[q++];
	for(int i = l; i <= r; i++) G[i] = tmp[i];
	return d;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		db x, y; scanf("%lf%lf", &x, &y);
		G.push_back(Pnt(x, y));
	}
	sort(G.begin(), G.end());
	printf("%.2lf ", Solve(0, n-1));
	printf("%.2lf\n", Getmax(ConvexHull(G)));
	return 0;
}
