#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 3e5 + 5;
const ll P = 1e9 + 21;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a - b + P : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll qpow(ll a, ll n) {ll ret = 1; for(; n; n >>= 1, a = a * a % P) if(n & 1) ret = ret * a % P; return ret;}
const ll inv2 = qpow(2, P-2), inv6 = qpow(6, P-2);
struct Node {
	ll mv, v, v2;
	void merge(const Node& a, const Node& b) {
		mv = min(a.mv, b.mv);
		v = pls(a.v, b.v);
		v2 = pls(a.v2, b.v2);
	}
	void apply(ll k) {
		mv = v = k % P; v2 = mul(k % P, k % P );
	}
}e[MAXN << 2];
#define ls p << 1
#define rs p << 1 | 1
void build(int p, int l, int r, ll a[]) {
	if(l == r) {
		e[p].apply(a[l]);
		return ;
	}
	int m = (l + r) >> 1;
	build(ls, l, m, a); build(rs, m+1, r, a);
	e[p].merge(e[ls], e[rs]);
}
void mdypos(int p, int l, int r, int x, ll k) {
	if(l == r) {
		e[p].apply(k);
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m) mdypos(ls, l, m, x, k);
	else mdypos(rs, m+1, r, x, k);
	e[p].merge(e[ls], e[rs]);
}
Node qryrange(int p, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[p];
	int m = (l + r) >> 1;
	if(y <= m) return qryrange(ls, l, m, x, y);
	else if(x > m) return qryrange(rs, m+1, r, x, y);
	else {
		Node ans; ans.merge(qryrange(ls, l, m, x, y), qryrange(rs, m+1, r, x, y));
		return ans;
	}
}
#undef ls
#undef rs
int n, m;
ll a[MAXN], lans;
bool check(ll l, ll r, ll k) {
	Node t = qryrange(1, 1, n, l, r);
	ll k1 = (n * t.mv % P + k * n % P * (n-1) % P * inv2 % P) % P;
	ll k2 = (n * t.mv % P * t.mv % P + 2 * k * n % P * (n-1) % P * inv2 % P + k * k % P * n % P * (n-1) % P * (2 * n - 1) % P * inv6 % P) % P;
	return k1 == t.v % P && k2 == t.v2 % P;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	build(1, 1, n, a);
	for(int i = 1; i <= m; i++) {
		int op = read();
		if(op == 1) {
			int x = read()^lans; ll y = read()^lans;
			mdypos(1, 1, n, x, y);
		} else {
			int l = read()^lans, r = read()^lans, k = read()^lans;
			if(check(l, r, k)) {
				lans++;
				printf("Yes\n");
			} else printf("No\n");
		}
	}
	return 0;
}
