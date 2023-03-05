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
const int MAXN = 1e5 + 5;
const db eps = 1e-8;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
db Abs(db x) {return x * dcmp(x);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) :x(x), y(y) {}
	void Read() {scanf("%lf%lf", &x, &y);}
};
typedef Pnt Vec;
Pnt operator + (const Pnt& a, const Pnt& b) {return Pnt(a.x + b.x, a.y + b.y);}
Pnt operator - (const Pnt& a, const Pnt& b) {return Pnt(a.x - b.x, a.y - b.y);}
Pnt operator * (const Pnt& a, const db& b) {return Pnt(a.x * b, a.y * b);}
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
db Len(const Vec& a) {return sqrt(Dot(a, a));}
db Dist(const Pnt& a, const Pnt& b) {return Len(b-a);}
db Angle(const Vec& a, const Vec& b) {return acos(Dot(a, b) / Len(a) / Len(b));}
bool operator == (const Pnt& a, const Pnt& b) {return !dcmp(a.x - b.x) && !dcmp(a.y - b.y);}
Pnt Footpoint(const Pnt& p, const Pnt& a, const Pnt& b) {
	Vec ap = p-a, bp = p-b, ab = b-a;
	db l1 = Dot(ap, ab) / Len(ab), l2 = -Dot(bp, ab) / Len(ab);
	return a + ab * (l1 / (l1 + l2));
}
Pnt Mindispoint(const Pnt& p, const Pnt& a, const Pnt& b) {
	if(a == b) return a;
	Vec ap = p-a, bp = p-b, ab = b-a;
	if(dcmp(Dot(ap, ab) < 0)) return a;
	if(dcmp(Dot(bp, ab) > 0)) return b;
	return Footpoint(p, a, b);
}

Pnt M, lst, now, ans;
int n;
int main() {
	while(scanf("%lf%lf\n", &M.x, &M.y) != EOF) {
		n = read(); lst.Read(); ans = lst;
		for(int i = 1; i <= n; i++) {
			now.Read();
			Pnt ret = Mindispoint(M, lst, now);
			if(dcmp(Dist(M, ret) - Dist(M, ans)) < 0) ans = ret;
			lst = now;
		}
		printf("%.4lf\n%.4lf\n", ans.x, ans.y);
	}
	return 0;
}
