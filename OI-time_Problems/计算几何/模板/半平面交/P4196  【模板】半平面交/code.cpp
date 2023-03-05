#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
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
const db eps = 1e-8;
const int MAXN = 1005;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) : x(x), y(y) {}
};
typedef Pnt Vec;
typedef vector<Pnt> poly;
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
bool operator == (const Vec& a, const Vec& b) {return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;}
int dir(const Pnt& p, const Pnt& a, const Pnt& b) {return dcmp(Cro(p - a, b - a));}
struct Line {
	Pnt a, b;
	db k;
	Line(Pnt A = Pnt(0, 0), Pnt B = Pnt(0, 0)) {
		a = A; b = B; k = atan2(b.y - a.y, b.x - a.x);
	}
};
int dir(const Pnt& p, const Line& l) {return dir(p, l.a, l.b);}
bool operator < (const Line& p, const Line& q) {
	return dcmp(p.k - q.k) == 0 ? dir(p.a, q) == -1 : p.k < q.k;
}
Pnt CrossPoint (const Pnt& a, const Pnt& b, const Pnt& c, const Pnt& d) {
	Vec ab = b-a, cd = d-c, ca = a-c;
	return a + ab * (Cro(cd, ca) / Cro(ab, cd));
}
Pnt CrossPoint(const Line& p, const Line& q) {return CrossPoint(p.a, p.b, q.a, q.b);}
poly Halfplanecut(vector<Line> G) {
	sort(G.begin(), G.end());
	int n = 0;
	for(int i = 1; i < (int)G.size(); i++)
		if(dcmp(G[i].k - G[i-1].k)) G[++n] = G[i];
	n++; G.resize(n);
	static int que[MAXN];
	int hd = 1, tl = 0;
	for(int i = 0; i < n; i++) {
		while(hd < tl && dir(CrossPoint(G[que[tl]], G[que[tl-1]]), G[i]) > 0) --tl;
		while(hd < tl && dir(CrossPoint(G[que[hd]], G[que[hd+1]]), G[i]) > 0) ++hd;
		que[++tl] = i;
	}
	while(hd < tl && dir(CrossPoint(G[que[tl]], G[que[tl-1]]), G[que[hd]]) > 0) --tl;
	while(hd < tl && dir(CrossPoint(G[que[hd]], G[que[hd+1]]), G[que[tl]]) > 0) ++hd;
	poly ans;
	for(int i = hd; i <= tl; i++) {
		int j = i == tl ? hd : i + 1;
		ans.push_back(CrossPoint(G[que[i]], G[que[j]]));
	}
	return ans;//逆
}
db Area(const poly& G) {
	db ans = 0; int n = G.size();
	for(int i = 0; i < n; i++) {
		int j = i == n-1 ? 0 : i+1;
		ans += Cro(G[i], G[j]);
	}
	return ans / 2;
}
int n, m;
Pnt a[MAXN];
vector<Line> H;
poly G;
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		m = read();
		for(int j = 0; j < m; j++) a[j].x = read(), a[j].y = read();
		for(int j = 0; j < m; j++) {
			int nxt = j == m-1 ? 0 : j+1;
			H.push_back(Line(a[j], a[nxt]));
		}
	}
	sort(H.begin(), H.end());
	G = Halfplanecut(H);
	printf("%.3lf\n", Area(G));
	return 0;
}
