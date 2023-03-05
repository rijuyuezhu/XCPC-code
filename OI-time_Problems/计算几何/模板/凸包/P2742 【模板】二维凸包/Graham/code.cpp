#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
typedef double db;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e5 + 5;
const db eps = 1e-8, inf = 1e10;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
db Abs(db x) {return x * dcmp(x);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) : x(x), y(y) {}
};
typedef Pnt Vec;
typedef vector<Pnt> Poly;
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
db Len(const Vec& a) {return sqrt(Dot(a, a));}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
bool operator == (const Pnt& a, const Pnt& b) {return !dcmp(a.x - b.x) && !dcmp(a.y - b.y);}
bool cmp(const Pnt& a, const Pnt& b) {return dcmp(a.x - b.x) == 0 ? a.y < b.y : a.x < b.x;}
Poly ConvexHull(Poly G) {
	static int st[MAXN];
	int _st = 0;
	sort(G.begin(), G.end(), cmp);
	unique(G.begin(), G.end());
	if(G.size() <= 2) return G;
	int n = G.size();
	st[++_st] = 0; st[++_st] = 1;
	for(int i = 2; i < n; i++) {
		while(_st > 1 && Cro(G[st[_st]]-G[st[_st-1]], G[i]-G[st[_st]]) >= 0) _st--;
		st[++_st] = i;
	}
	int t = _st; st[++_st] = n-2;
	for(int i = n-3; i >= 0; i--) {
		while(_st > t && Cro(G[st[_st]]-G[st[_st-1]], G[i]-G[st[_st]]) >= 0) _st--;
		st[++_st] = i;
	}
	Poly T;
	for(int i = 1; i < _st; i++) T.push_back(G[st[i]]);
	return T;
}
db Circum(const Poly& G) {
	db ans = 0;
	int n = G.size();
	for(int i = 0; i < n; i++) {
		int j = (i+1) % n;
		ans += Len(G[j]-G[i]);
	}
	return ans;
}
int n;
Poly G;
int main() {
	n = read();
	Pnt tmp;
	G.resize(n);
	for(int i = 1; i <= n; i++) {
		scanf("%lf%lf", &tmp.x, &tmp.y);
		G[i-1] = tmp;
	}
	G = ConvexHull(G);
	printf("%.2lf\n", Circum(G));
	return 0;
}
