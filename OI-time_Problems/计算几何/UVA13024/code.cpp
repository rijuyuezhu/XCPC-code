#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 1e4 + 5;
struct Pnt {
	ll x, y;
	Pnt(ll x = 0, ll y = 0) :x(x), y(y) {}
};
typedef Pnt Vec;
typedef vector<Pnt> Poly;
ll Dot(const Pnt& a, const Pnt& b) {return a.x * b.x + a.y * b.y;}
ll Cro(const Pnt& a, const Pnt& b) {return a.x * b.y - a.y * b.x;}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const ll& b) {return Vec(a.x * b, a.y * b);}
bool isPointonSeg(const Pnt& p, const Pnt& a, const Pnt& b) {
	return Cro(p-a, b-a) == 0 && Dot(p-a, p-b) <= 0;
}
bool cmp(const Pnt& a, const Pnt& b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
Poly ConvexHull(Poly G) {//shun tubao
	static int stk[MAXN];
	int _stk = 0;
	sort(G.begin(), G.end(), cmp);
	int n = G.size();
	stk[++_stk] = 0, stk[++_stk] = 1;
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
int L, S;
Poly G;
int main() {
	while(scanf("%d", &L) != EOF) {
		G.clear();
		for(int i = 1; i <= L; i++) {
			Pnt tmp;
			tmp.x = read(), tmp.y = read();
			G.push_back(tmp);
		}
		G = ConvexHull(G);
		S = read();
		int cnt = 0;
		for(int i = 1; i <= S; i++) {
			Pnt tmp;
			tmp.x = read(), tmp.y = read();
			if(PIP(tmp, G) >= 1) cnt++;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
