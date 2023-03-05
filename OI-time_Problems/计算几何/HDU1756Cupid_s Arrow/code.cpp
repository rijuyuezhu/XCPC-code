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
const int MAXN = 105;
const db eps = 1e-8;
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
bool isPointonSeg(const Pnt& p, const Pnt& a, const Pnt& b) {
	return !dcmp(Cro(p-a, b-a)) && dcmp(Dot(p-a, p-b)) <= 0;
}
int PIP(const Pnt& p, const Poly& G) {
	int cnt = 0;
	for(int i = 0; i < G.size(); i++) {
		int j = (i == G.size()-1) ? 0 : i+1;
		if(isPointonSeg(p, G[i], G[j])) return 2;
		if(p.y >= min(G[i].y, G[j].y) && p.y < max(G[i].y, G[j].y)) {
			db tmp = G[i].x + (p.y - G[i].y) / (G[j].y - G[i].y) * (G[j].x - G[i].x);
			if(dcmp(tmp - p.x) > 0) cnt++;
		}
	}
	return cnt & 1;
}
int n, m;
Poly G;
Pnt a;
int main() {
	while(scanf("%d", &n) != EOF) {
		G.clear();
		for(int i = 1; i <= n; i++) {
			Pnt tmp;
			scanf("%lf%lf", &tmp.x, &tmp.y);
			G.push_back(tmp);
		}
		m = read();
		for(int i = 1; i <= m; i++) {
			scanf("%lf%lf", &a.x, &a.y);
			if(PIP(a, G) >= 1) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}
