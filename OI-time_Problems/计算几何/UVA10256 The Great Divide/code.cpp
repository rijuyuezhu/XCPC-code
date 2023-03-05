#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 505;
struct Pnt {
	int x, y;
	Pnt(int x = 0, int y = 0) :x(x), y(y) {}
};
typedef Pnt Vec;
typedef vector<Pnt> Poly;
int Dot(const Pnt& a, const Pnt& b) {return a.x * b.x + a.y * b.y;}
int Cro(const Pnt& a, const Pnt& b) {return a.x * b.y - a.y * b.x;}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const int& b) {return Vec(a.x * b, a.y * b);}
bool cmp(const Pnt& a, const Pnt& b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
bool operator == (const Pnt& a, const Pnt& b) {return a.x == b.x && a.y == b.y;}
bool isPointonSeg(const Pnt& p, const Pnt& a, const Pnt& b) {
	return Cro(p-a, b-a) == 0 && Dot(p-a, p-b) <= 0;
}
Poly ConvexHull(Poly G) {//shun
	static int stk[MAXN];
	int _stk = 0;
	sort(G.begin(), G.end(), cmp);
	unique(G.begin(), G.end());
	if(G.size() <= 2) return G;
	int n = G.size();
	stk[++_stk] = 0; stk[++_stk] = 1;
	for(int i = 2; i < n; i++) {
		while(_stk > 1 && Cro(G[stk[_stk]]-G[stk[_stk-1]], G[i]-G[stk[_stk]]) >= 0) --_stk;
		stk[++_stk] = i;
	}
	int t = _stk; stk[++_stk] = n-2;
	for(int i = n-3; i >= 0; i--) {
		while(_stk > t && Cro(G[stk[_stk]]-G[stk[_stk-1]], G[i]-G[stk[_stk]]) >= 0) --_stk;
		stk[++_stk] = i;
	}
	Poly T;
	for(int i = 1; i < _stk; i++) T.push_back(G[stk[i]]);
	return T;
}
int PIP(const Pnt& p, const Poly& G) {//shun
	int n = G.size();
	if(n == 1) return p == G[0] ? 2 : 0;
	else if(n == 2) return isPointonSeg(p, G[0], G[1]) ? 2 : 0;
	if(Cro(p-G[0], G[1]-G[0]) < 0 || Cro(p-G[0], G[n-1]-G[0]) > 0) return 0;
	if(isPointonSeg(p, G[0], G[1]) || isPointonSeg(p, G[0], G[n-1])) return 2;
	int l = 1, r = n-2, t = -1;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(Cro(p-G[0], G[m]-G[0]) > 0) t = m, l = m + 1;
		else r = m - 1;
	}
	if(t == -1) return 0;
	if(Cro(p-G[t], G[t+1]-G[t]) < 0) return 0;
	if(isPointonSeg(p, G[t], G[t+1])) return 2;
	return 1;
}
bool isCrossSegSeg(const Pnt& a, const Pnt& b, const Pnt& c, const Pnt& d) {
	if(max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, d.x) || max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) return 0;
	if(1ll * Cro(c-a, b-a) * Cro(d-a, b-a) > 0 || 1ll * Cro(a-c, d-c) * Cro(b-c, d-c) > 0) return 0;
	return 1;
}
bool isawayPolyPoly(const Poly& A, const Poly& B) {
	for(int i1 = 0; i1 < A.size(); i1++) {
		int j1 = (i1+1) % A.size();
		for(int i2 = 0; i2 < B.size(); i2++) {
			int j2 = (i2+1) % B.size();
			if(isCrossSegSeg(A[i1], A[j1], B[i2], B[j2])) return 0;
		}
	}
	if(PIP(A[0], B) || PIP(B[0], A)) return 0;
	return 1;
}
int n, m;
Poly A, B;
int main() {
	while(1) {
		n = read(); m = read();
		if(!n && !m) break;
		A.clear(); B.clear();
		Pnt a;
		for(int i = 1; i <= n; i++) {
			a.x = read(); a.y = read();
			A.push_back(a);
		}
		for(int i = 1; i <= m; i++) {
			a.x = read(); a.y = read();
			B.push_back(a);
		}
		A = ConvexHull(A); B = ConvexHull(B);
		if(isawayPolyPoly(A, B)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
