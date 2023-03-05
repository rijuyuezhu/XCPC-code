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
const int MAXN = 5e4 + 5;
struct Item {ll k, a, b, c;}q[MAXN], q1[MAXN], q2[MAXN];
int n, m, qry_num, ans[MAXN], tot;
namespace Sgt {
#define ls p << 1
#define rs p << 1 | 1
	struct Node{ll sum, tag;}e[MAXN << 2];
	void upd(int p) {e[p].sum = e[ls].sum + e[rs].sum;}
	void psdadd(int p, int l, int r, ll k) {
		e[p].sum += k * (r - l + 1);
		e[p].tag += k;
	}
	void psd(int p, int l, int r) {
		if(e[p].tag) {
			int m = (l + r) >> 1;
			psdadd(ls, l, m, e[p].tag);
			psdadd(rs, m+1, r, e[p].tag);
			e[p].tag = 0;
		}
	}
	void addrange(int p, int l, int r, int x, int y, ll k) {
		if(x <= l && r <= y) {psdadd(p, l, r, k); return;}
		int m = (l + r) >> 1;
		psd(p, l, r);
		if(x <= m) addrange(ls, l, m, x, y, k);
		if(y > m) addrange(rs, m+1, r, x, y, k);
		upd(p);
	}
	ll qryrange(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p].sum;
		int m = (l + r) >> 1;
		psd(p, l, r);
		if(y <= m) return qryrange(ls, l, m, x, y);
		else if(x > m) return qryrange(rs, m+1, r, x, y);
		else return qryrange(ls, l, m, x, m) + qryrange(rs, m+1, r, m+1, y);
	}
#undef ls
#undef rs
}
void solve(int kl, int kr, int l, int r) {
	if(kl > kr) return;
	if(l == r) {
		for(int i = kl; i <= kr; i++) if(q[i].k) ans[q[i].k] = l;
		return ;
	}
	int m = (l + r) >> 1, k1 = 0, k2 = 0;
	for(int i = kl; i <= kr; i++) 
		if(!q[i].k) {
			if(q[i].c > m) {
				Sgt::addrange(1, 1, n, q[i].a, q[i].b, 1);
				q2[++k2] = q[i];
			} else q1[++k1] = q[i];
		} else {
			ll t = Sgt::qryrange(1, 1, n, q[i].a, q[i].b);
			if(q[i].c <= t) q2[++k2] = q[i];
			else {
				q[i].c -= t;
				q1[++k1] = q[i];
			}
		}
	for(int i = 1; i <= k2; i++) if(!q2[i].k) Sgt::addrange(1, 1, n, q2[i].a, q2[i].b, -1);
	for(int i = 1; i <= k1; i++) q[kl+i-1] = q1[i];
	for(int i = 1; i <= k2; i++) q[kl+k1+i-1] = q2[i];
	solve(kl, kl+k1-1, l, m); solve(kl+k1, kr, m+1, r);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		int opt = read(), l = read(), r = read(), c = read();
		if(opt == 1) q[++tot] = (Item){0, l, r, c};
		else q[++tot] = (Item){++qry_num, l, r, c};
	}
	solve(1, tot, -n, n);
	for(int i = 1; i <= qry_num; i++) printf("%d\n", ans[i]);
	return 0;
}
