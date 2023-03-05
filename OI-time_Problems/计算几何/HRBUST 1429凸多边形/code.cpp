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
const int MAXN = 1e5 + 5;
const db eps = 1e-8;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
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
Vec operator * (const Vec& a, const db& b) {return Vec(a.x - b, a.y - b);}
bool isPointonSeg(const Pnt& p, const Pnt& a, const Pnt& b) {
	return !dcmp(Cro(p-a, b-a)) && dcmp(Dot(p-a, p-b)) <= 0;
}
int PIP(const Pnt& p, const Poly& G) {//G shun
	int n = G.size();
	if(dcmp(Cro(p-G[0], G[1]-G[0]) < 0) || dcmp(Cro(p-G[0], G[n-1]-G[0])) > 0) return 0;
	if(isPointonSeg(p, G[0], G[1]) || isPointonSeg(p, G[0], G[n-1])) return 2;
	int l = 1, r = n-2, t = -1;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(dcmp(Cro(p-G[0], G[m]-G[0])) > 0) t = m, l = m+1;
		else r = m-1;
	}
	if(t == -1) return 0;
	if(dcmp(Cro(p-G[t], G[t+1]-G[t])) < 0) return 0;
	if(isPointonSeg(p, G[t], G[t+1])) return 2;
	return 1;
}
int n, m;
Poly G;
Pnt B;
int main() {
	while(scanf("%d", &n) != EOF) {
		G.clear();
		for(int i = 1; i <= n; i++) {
			Pnt tmp;
			scanf("%lf%lf", &tmp.x, &tmp.y);
			G.push_back(tmp);
		}
		m = read(); 
		bool fl = 1;
		for(int i = 1; i <= m; i++) {
			scanf("%lf%lf", &B.x, &B.y);
			if(PIP(B, G) != 1) fl = 0;
		}
		printf(fl ? "YES\n" : "NO\n");
	}
	return 0;
}
