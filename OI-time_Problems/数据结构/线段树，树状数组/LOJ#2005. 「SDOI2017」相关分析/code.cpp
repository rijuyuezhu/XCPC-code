#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m;
db initx[MAXN], inity[MAXN], si[MAXN], si2[MAXN];
#define ls p << 1
#define rs p << 1 | 1
#define len (r-l+1)
struct Node {
	db a, b, c, d, aS, aT, mS, mT;
	void apply(ll x, ll y) {
		a = x * y;
		b = x;
		c = y;
		d = x * x;
	}
	void merge(const Node& x, const Node& y) {
		a = x.a + y.a;
		b = x.b + y.b;
		c = x.c + y.c;
		d = x.d + y.d;
	}
}e[MAXN << 2];
void psdm(int p, int l, int r, db S, db T) {
	e[p].aS = e[p].aT = 0; e[p].mS = S; e[p].mT = T;
	e[p].a = (si2[r] - si2[l-1]) + (S + T) * (si[r] - si[l-1]) + len * S * T;
	e[p].b = (si[r] - si[l-1]) + len * S;
	e[p].c = (si[r] - si[l-1]) + len * T;
	e[p].d = (si2[r] - si2[l-1]) + 2 * S * (si[r] - si[l-1]) + len * S * S;
}
void psda(int p, int l, int r, db S, db T) {
	if(e[p].mS != INF) {
		psdm(p, l, r, S + e[p].mS, T + e[p].mT);
		return ;
	}
	e[p].aS += S; e[p].aT += T;
	e[p].a += T * e[p].b + S * e[p].c + len * S * T;
	e[p].d += 2 * S * e[p].b + len * S * S;
	e[p].b += len * S;
	e[p].c += len * T;
}
void psd(int p, int l, int r) {
	int m = (l + r) >> 1;
	if(e[p].mS != INF) {
		psdm(ls, l, m, e[p].mS, e[p].mT);
		psdm(rs, m+1, r, e[p].mS, e[p].mT);
		e[p].mS = e[p].mT = INF;
	} else if(e[p].aS || e[p].aT) {
		psda(ls, l, m, e[p].aS, e[p].aT);
		psda(rs, m+1, r, e[p].aS, e[p].aT);
		e[p].aS = e[p].aT = 0;
	}
}
void build(int p, int l, int r) {
	e[p].mS = e[p].mT = INF;
	e[p].aS = e[p].aT = 0;
	if(l == r) {
		e[p].apply(initx[l], inity[l]);
		return ;
	}
	int m = (l + r) >> 1;
	build(ls, l, m); build(rs, m+1, r);
	e[p].merge(e[ls], e[rs]);
}
Node qryrange(int p, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[p];
	psd(p, l, r);
	int m = (l + r) >> 1;
	if(y <= m) return qryrange(ls, l, m, x, y);
	else if(x > m) return qryrange(rs, m+1, r, x, y);
	else {
		Node ans;
		ans.merge(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y));
		return ans;
	}
}
void addrange(int p, int l, int r, int x, int y, int S, int T) {
	if(x <= l && r <= y) {
		psda(p, l, r, S, T);
		return ;
	}
	psd(p, l, r);
	int m = (l + r) >> 1;
	if(x <= m) addrange(ls, l, m, x, y, S, T);
	if(y > m) addrange(rs, m+1, r, x, y, S, T);
	e[p].merge(e[ls], e[rs]);
}
void mdyrange(int p, int l, int r, int x, int y, int S, int T) {
	if(x <= l && r <= y) {
		psdm(p, l, r, S, T);
		return ;
	}
	psd(p, l, r);
	int m = (l + r) >> 1;
	if(x <= m) mdyrange(ls, l, m, x, y, S, T);
	if(y > m) mdyrange(rs, m+1, r, x, y, S, T);
	e[p].merge(e[ls], e[rs]);
}
#undef ls
#undef rs
#undef len
int main() {
	//freopen("relative.in", "r", stdin);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) initx[i] = read();
	for(int i = 1; i <= n; i++) inity[i] = read();
	for(int i = 1; i <= n; i++) si[i] = si[i-1] + i;
	for(int i = 1; i <= n; i++) si2[i] = si2[i-1] + 1ll * i * i;
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int opt = read(), l = read(), r = read();
		if(opt == 1) {
			Node t = qryrange(1, 1, n, l, r);
			db u = (r-l+1) * t.a - t.b * t.c, v = (r-l+1) * t.d - t.b * t.b;
			printf("%.10lf\n", double(u) / v);
		} else if(opt == 2) {
			db S = read(), T = read();
			addrange(1, 1, n, l, r, S, T);
		} else {
			db S = read(), T = read();
			mdyrange(1, 1, n, l, r, S, T);
		}
	}
	return 0;
}
