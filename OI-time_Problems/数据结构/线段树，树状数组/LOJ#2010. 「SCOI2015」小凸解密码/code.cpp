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
int readop() {
	char ch = getchar();
	for(; ch != '+' && ch != '*'; ch = getchar());
	return ch == '*';
}
const int MAXN = 2e5 + 5;
int n, m;
namespace Sgt {
	#define ls p << 1
	#define rs p << 1 | 1
	struct Node {
		int u, lv, rv, c;
		void apply(int v) {
			if(v) u = lv = rv = 1, c = 0;
			else u = lv = rv = 0, c = 0;
		}
		void merge(const Node& a, const Node& b) {
			u = a.u + b.u;
			lv = a.lv; rv = b.rv;
			c = a.c || b.c;
			if(a.u && b.u && (!a.rv || !b.lv)) c = 1;
		}
	}e[MAXN << 2];
	void build(int p, int l, int r, int v[]) {
		if(l == r) {
			e[p].apply(v[l]);
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, v); build(rs, m+1, r, v);
		e[p].merge(e[ls], e[rs]);
	}
	void mdypos(int p, int l, int r, int x, int v) {
		if(l == r) {
			e[p].apply(v);
			return ;
		}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(ls, l, m, x, v);
		else mdypos(rs, m+1, r, x, v);
		e[p].merge(e[ls], e[rs]);
	}
	Node qryrange(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p];
		int m = (l + r) >> 1;
		if(y <= m) return qryrange(ls, l, m, x, y);
		else if(x > m) return qryrange(rs, m+1, r, x, y);
		else {
			Node ans;
			ans.merge(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y));
			return ans;
		}
	}
	void print(int p, int l, int r) {
		if(l == r) {
			printf("%d ", e[p].u);
			return ;
		}
		int m = (l + r) >> 1;
		print(ls, l, m);
		print(rs, m+1, r);
	}
	#undef ls
	#undef rs
}
using namespace Sgt;
int a[MAXN], t[MAXN], b[MAXN];
//+ : 0, * : 1
void calc(int i) {
	if(t[i]) b[i] = (a[i-1] * a[i]) % 10;
	else b[i] = (a[i-1] + a[i]) % 10;
}
void mdy(int i, int num, int opt) {
	a[i] = num; t[i] = opt; a[i+n] = num; t[i+n] = opt;
	calc(i); mdypos(1, 1, 2*n, i, b[i]);
	calc(i+1); mdypos(1, 1, 2*n, i+1, b[i+1]);
	calc(i+n); mdypos(1, 1, 2*n, i+n, b[i+n]);
	if(i < n) {
		calc(i+1+n); mdypos(1, 1, 2*n, i+1+n, b[i+1+n]);
	}
}
int qry(int pos) {
	int ans = -1;
	int l = 1, r = n / 2;
	mdypos(1, 1, 2*n, pos, a[pos]);
	mdypos(1, 1, 2*n, pos+n, a[pos+n]);
	while(l <= r) {
		int m = (l + r) >> 1;
		Node ret = qryrange(1, 1, 2*n, pos + m - 1, pos + n - m + 1);
		if(ret.c) ans = m, l = m + 1;
		else r = m - 1;
	}
	if(ans == -1) {
		Node ret = qryrange(1, 1, 2*n, pos, pos + n - 1);
		if(ret.u != n) ans = 0;
	}
	mdypos(1, 1, 2*n, pos, b[pos]);
	mdypos(1, 1, 2*n, pos+n, b[pos+n]);
	return ans;
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read() % 10, t[i] = readop();
		a[i+n] = a[i]; t[i+n] = t[i];
	}
	for(int i = 1; i <= 2*n; i++) calc(i);
	build(1, 1, 2*n, b);
	for(int i = 1; i <= m; i++) {
		int opt = read();
		if(opt == 1) {
			int pos = read()+1, num = read() % 10, opt = readop();
			mdy(pos, num, opt);
		} else {
			int pos = read()+1;
			printf("%d\n", qry(pos));
		}
	}
	return 0;
}
