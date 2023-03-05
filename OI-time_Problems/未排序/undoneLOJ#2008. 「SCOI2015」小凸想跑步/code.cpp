#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const db eps = 1e-8;
const int MAXN = 5e5 + 5;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) :x(x), y(y) {}
};
typedef Pnt Vec;
typedef vector<Pnt> Poly;
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
bool operator == (const Vec& a, const Vec& b) {return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;}
struct Line {
	Pnt o, v;
	db K;
	Line(Pnt O = Pnt(0, 0), Pnt V = Pnt(0, 0)) {
		o = O; v = V; K = atan2(v.y, v.x);
	}
};
int dir(const Pnt& p, const Line& l) {return dcmp(Cro(p - l.o, l.v));}
Pnt CrossPoint(const Line& p, const Line& q) {
	Vec t = p.o - q.o;
	return p.o + p.v * (Cro(q.v, t) / Cro(p.v, q.v));
}
bool cmp(const Line& a, const Line& b) {
	return dcmp(a.K - b.K) ? a.K < b.K : dir(a.o, b) < 0;
}
Poly Halfplanecut(vector<Line> G) {
	sort(G.begin(), G.end(), cmp);
	int n = 0;
	for(int i = 1; i < (int)G.size(); i++)
		if(dcmp(G[i].K - G[i-1].K)) G[++n] = G[i];
	++n; G.resize(n);
	static int que[MAXN];
	int hd = 1, tl = 0;
	for(int i = 0; i < n; i++) {
		while(hd < tl && dir(CrossPoint(G[que[tl]], G[que[tl-1]]), G[i]) > 0) tl--;
		while(hd < tl && dir(CrossPoint(G[que[hd]], G[que[hd+1]]), G[i]) > 0) hd++;
		que[++tl] = i;
	}
	while(hd < tl && dir(CrossPoint(G[que[tl]], G[que[tl-1]]), G[hd]) > 0) tl--;
	while(hd < tl && dir(CrossPoint(G[que[hd]], G[que[hd+1]]), G[tl]) > 0) hd++;
	Poly ans;
	for(int i = hd; i <= tl; i++) {
		int nxt = i == tl ? hd : i+1;
		ans.push_back(CrossPoint(G[que[i]], G[que[nxt]]));
	}
	return ans;//逆
}
db Area(const Poly& G) {
	db ans = 0; int n = G.size();
	for(int i = 0; i < n; i++) {
		int nxt = i == n-1 ? 0 : i+1;
		ans += Cro(G[i], G[nxt]);
	}
	return ans / 2;
}
int n;
Poly G;
vector<Line> H;
db S1, S2;
int main() {
	n = read(); G.resize(n);
	for(int i = 0; i < n; i++) G[i].x = read(), G[i].y = read();
	S1 = Area(G);
	for(int i = 0; i < n; i++) {
		int nxt = i == n-1 ? 0 : i+1;
		H.push_back(Line(G[i], G[nxt] - G[i]));
	}
	for(int i = 1; i < n; i++) {
		int nxt = i == n-1 ? 0 : i+1;
		db A = G[0].y - G[1].y + G[nxt].y - G[i].y,
		   B = G[1].x - G[0].x + G[i].x - G[nxt].x,
		   C = G[0].x * G[1].y - G[1].x * G[0].y + G[nxt].x * G[i].y - G[i].x * G[nxt].y;
		if(dcmp(A))
			H.push_back(Line(Pnt(-C / A, 0), Pnt(-B, A)));
		else 
			H.push_back(Line(Pnt(0, -C / B), Pnt(-B, A)));
	}
	G = Halfplanecut(H);
	S2 = Area(G);
	printf("%.4lf\n", S2 / S1);
	return 0;
}
