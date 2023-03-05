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
char readc() {
	char ch = getchar();
	for(; ch != 'Q' && ch != 'C'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
const int MAXV = 2e5 + 5;
int n, m, lsh[MAXV], lsh_num, a[MAXN];
struct Item {
	int k, a, b, c;
}q[MAXM];
void LSH() {
	sort(lsh + 1, lsh + 1 + lsh_num);
	lsh_num = unique(lsh + 1, lsh + 1 + lsh_num) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + lsh_num, x) - lsh;
}
namespace Sgt {
	const int MAXNODE = 3e7;
	struct Node{int ls, rs, sz;}e[MAXNODE];
	int tot, limtot;
	bool bklim() {return tot > 2.85e7;}
	void setlim() {limtot = tot;}
	void mdy(int& p, int pre, int l, int r, int x, int v) {
		if(pre <= limtot) p = ++tot, e[p] = e[pre];
		else p = pre;
		e[p].sz += v;
		if(l == r) return;
		int m = (l + r) >> 1;
		if(x <= m) mdy(e[p].ls, e[pre].ls, l, m, x, v);
		else mdy(e[p].rs, e[pre].rs, m+1, r, x, v);
	}
	int A[MAXN], B[MAXN], totA, totB;
	int qry(int l, int r, int k) {
		if(l == r) return lsh[l];
		int fl = 0;
		for(int i = 1; i <= totA; i++) fl += e[e[A[i]].ls].sz;
		for(int i = 1; i <= totB; i++) fl -= e[e[B[i]].ls].sz;
		int m = (l + r) >> 1;
		if(k <= fl) {
			for(int i = 1; i <= totA; i++) A[i] = e[A[i]].ls;
			for(int i = 1; i <= totB; i++) B[i] = e[B[i]].ls;
			return qry(l, m, k);
		} else {
			for(int i = 1; i <= totA; i++) A[i] = e[A[i]].rs;
			for(int i = 1; i <= totB; i++) B[i] = e[B[i]].rs;
			return qry(m+1, r, k - fl);
		}
	}
}
namespace BIT {
	int rt[MAXN];
	int lowbit(int x) {return x&-x;}
	void build(int a[]) {
		for(int k = 1; k <= n; k++) {
			Sgt::setlim();
			for(int i = k - lowbit(k) + 1; i <= k; i++)
				Sgt::mdy(rt[k], rt[k], 1, lsh_num, a[i], 1);
		}
	}
	void mdy(int x, int fr, int to) {
		for(int i = x; i <= n; i += lowbit(i)) {
			Sgt::setlim();
			Sgt::mdy(rt[i], rt[i], 1, lsh_num, fr, -1);
			Sgt::mdy(rt[i], rt[i], 1, lsh_num, to, 1);
		}
	}
	int qry(int x, int y, int k) {
		Sgt::totA = Sgt::totB = 0;
		for(int i = y; i; i -= lowbit(i)) Sgt::A[++Sgt::totA] = rt[i];
		for(int i = x-1; i; i -= lowbit(i)) Sgt::B[++Sgt::totB] = rt[i];
		return Sgt::qry(1, lsh_num, k);
	}
}
int main() {
	//freopen("code.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) lsh[++lsh_num] = a[i] = read();
	for(int i = 1; i <= m; i++) {
		char opt = readc(); Item& now = q[i];
		if(opt == 'Q') {
			now.k = 1; now.a = read(), now.b = read(), now.c = read();
		} else {
			now.k = 2; now.a = read(); lsh[++lsh_num] = now.b = read();
		}
	}
	LSH();
	for(int i = 1; i <= n; i++) a[i] = LSH(a[i]);
	for(int i = 1; i <= m; i++) if(q[i].k == 2) q[i].b = LSH(q[i].b);
	BIT::build(a);
	for(int i = 1; i <= m; i++) {
		Item now = q[i];
		if(now.k == 1) {
			printf("%d\n", BIT:: qry(now.a, now.b, now.c));
		} else {
			if(Sgt::bklim()) {
				a[now.a] = now.b;
				Sgt::tot = 0; memset(BIT::rt, 0x00, sizeof(int) * (n+1));
				BIT::build(a);
			} else {
				BIT::mdy(now.a, a[now.a], now.b);
				a[now.a] = now.b;
			}
		}
	}
	return 0;
}
