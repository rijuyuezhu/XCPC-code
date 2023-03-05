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
const int MAXN = 50005;
const db eps = 1e-8;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
int n, st[MAXN], _st, t[MAXN];
struct Line {
	db k, b; int id;
}a[MAXN];
bool cmp(const Line& a, const Line& b) {return dcmp(a.k - b.k) == 0 ? a.b > b.b : a.k < b.k;}
bool cover(int i, int j, int k) {
	db x = (a[i].b - a[j].b) / (a[j].k - a[i].k);
	db y = (a[j].k * a[i].b - a[i].k * a[j].b) / (a[j].k - a[i].k);
	return dcmp(y - a[k].k * x - a[k].b) >= 0;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i].k = read(), a[i].b = read(), a[i].id = i;
	sort(a + 1, a + 1 + n, cmp);
	int _n = 0;
	for(int i = 1; i <= n; i++) {
		if(i == 1 || dcmp(a[i].k - a[i-1].k) != 0) a[++_n] = a[i];
	}
	n = _n;
	st[++_st] = 1;
	for(int i = 2; i <= n; i++) {
		while(_st > 1 && cover(st[_st-1], i, st[_st])) --_st;
		st[++_st] = i;
	}
	for(int i = 1; i <= _st; i++) t[i] = a[st[i]].id;
	sort(t + 1, t + 1 + _st);
	for(int i = 1; i <= _st; i++) printf("%d ", t[i]);
	return 0;
}
