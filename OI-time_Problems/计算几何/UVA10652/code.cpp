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
const int MAXN = 2505;
const db eps = 1e-8;
const db PI = acos(-1.0);
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) :x(x), y(y) {}
};
typedef Pnt Vec;
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
db cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
db dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
Pnt turn(const Pnt& p, const db& rad) {return Pnt(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));}
bool cmp(const Pnt& a, const Pnt& b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
int n, tot, cv[MAXN], icv;
Pnt p[MAXN];
db S1, S2;
void work() {
	n = read(); S1 = S2 = 0; tot = 0;
	for(int i = 1; i <= n; i++) {
		db x0, y0, w, h, ph;
		scanf("%lf%lf%lf%lf%lf", &x0, &y0, &w, &h, &ph);
		Pnt cir = Pnt(x0, y0);
		Vec dx = turn(Vec(w / 2, 0), -ph / 180.0 * acos(-1.0)),
			dy = turn(Vec(0, h / 2), -ph / 180.0 * acos(-1.0));
		p[++tot] = cir + dx + dy;
		p[++tot] = cir + dx - dy;
		p[++tot] = cir - dx + dy;
		p[++tot] = cir - dx - dy;
		S1 += w * h;
	}
	sort(p + 1, p + 1 + tot, cmp);
	icv = 0;
	for(int i = 1; i <= tot; i++) {
		while(icv >= 2 && cro(p[cv[icv]] - p[cv[icv-1]], p[i] - p[cv[icv]]) <= 0) icv--;
		cv[++icv] = i;
	}
	int t = icv;
	for(int i = tot-1; i >= 1; i--) {
		while(icv >= t+1 && cro(p[cv[icv]] - p[cv[icv-1]], p[i] - p[cv[icv]]) <= 0) icv--;
		cv[++icv] = i;
	}
	for(int i = 1; i < icv; i++) 
		S2 += cro(p[cv[i]], p[cv[i+1]]);
	S2 /= 2;
	S2 = dcmp(S2) < 0 ? -S2 : S2;
	printf("%.1lf %%\n", 100 * S1 / S2);
}
int main() {
	for(int T = read(); T; T--) work();
	return 0;
}
