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
const int MAXN = 5e4 + 5;
int sgn(int x) {return x > 0 ? 1 : (x < 0 ? -1 : 0);}
struct Pnt {
	int x, y;
	Pnt(int x = 0, int y = 0) : x(x), y(y) {}
};
typedef Pnt Vec;
typedef vector<Pnt> Poly;
int Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
int Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
int Len2(const Vec& a) {return Dot(a, a);}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const int& b) {return Vec(a.x * b, a.y * b);}
bool cmp(const Pnt& a, const Pnt& b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
bool operator == (const Pnt& a, const Pnt& b) {return a.x == b.x && a.y == b.y;}
Poly ConvexHull(Poly G) {//ni
	sort(G.begin(), G.end(), cmp);
	unique(G.begin(), G.end(), cmp);
	if(G.size() <= 2) return G;
	static int st[MAXN];
	int _st = 0, n = G.size();
	st[++_st] = 0, st[++_st] = 1;
	for(int i = 2; i < n; i++) {
		while(_st > 1 && Cro(G[st[_st]]-G[st[_st-1]], G[i]-G[st[_st]]) <= 0) _st--;
		st[++_st] = i;
	}
	int t = _st; st[++_st] = n-2;
	for(int i = n-3; i >= 0; i--) {
		while(_st > t && Cro(G[st[_st]]-G[st[_st-1]], G[i]-G[st[_st]]) <= 0) _st--;
		st[++_st] = i;
	}
	Poly T(_st-1);
	for(int i = 1; i < _st; i++) T[i-1] = G[st[i]];
	return T;
}
int Getmax(const Poly& G) {//ni
	int n = G.size();
	if(n == 1) return 0;
	else if(n == 2) return Len2(G[1]-G[0]);
	int ans = Len2(G[1]-G[0]);
	for(int i = 0, j = 2; i < n; i++) {
		int i2 = (i+1) % n, j2 = (j+1) % n;
		while(Cro(G[i2]-G[i], G[j]-G[i]) < Cro(G[i2]-G[i], G[j2]-G[i])) j = j2, j2 = (j2+1) % n;
		ans = max(ans, max(Len2(G[j]-G[i]), Len2(G[j]-G[i2])));
	}
	return ans;
}
int n;
Poly G;
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		int x = read(), y = read();
		G.push_back(Pnt(x, y));
	}
	G = ConvexHull(G);
	printf("%d\n", Getmax(G));
	return 0;
}
