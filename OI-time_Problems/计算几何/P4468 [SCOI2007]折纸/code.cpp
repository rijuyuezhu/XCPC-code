#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
const int MAXN = 9;
const db eps = 1e-6;
db dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) :x(x), y(y) {}
};
typedef Pnt Vec;
Pnt operator + (const Pnt& a, const Pnt& b) {return Pnt(a.x + b.x, a.y + b.y);}
Pnt operator - (const Pnt& a, const Pnt& b) {return Pnt(a.x - b.x, a.y - b.y);}
Pnt operator * (const Pnt& a, const db& b) {return Pnt(a.x * b, a.y * b);}
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - b.x * a.y;}
db Len(const Vec& a) {return sqrt(Dot(a, a));}
Pnt Footpoint(const Pnt& p, const Pnt& a, const Pnt& b) {
	Vec ap = p - a, ab = b - a;
	return a + ab * (Dot(ap, ab) / Len(ab) / Len(ab));
}
Pnt Reflect(const Pnt& p, const Pnt& a, const Pnt& b) {
	return p + (Footpoint(p, a, b) - p) * 2;
}

int n, m;
Pnt fr[MAXN], to[MAXN];
int solve(Pnt t, int k) {
	if(!k) {
		return dcmp(t.x - 0) > 0 && dcmp(t.x - 100.0) < 0 && dcmp(t.y - 0) > 0 && dcmp(t.y - 100.0) < 0;
	}
	db v = Cro(t - fr[k], to[k] - fr[k]);
	if(dcmp(v) >= 0) return 0;
	return solve(t, k-1) + solve(Reflect(t, fr[k], to[k]), k-1);
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) 
		scanf("%lf%lf%lf%lf", &fr[i].x, &fr[i].y, &to[i].x, &to[i].y);
	m = read();
	for(int i = 1; i <= m; i++) {
		Pnt t; scanf("%lf%lf", &t.x, &t.y);
		printf("%d\n", solve(t, n));
	}
	return 0;
}
