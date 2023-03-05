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
	for(; ch < 'A' || ch > 'Z'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}

struct Frac {
	ll u, v;
	void calc() {
		ll g = gcd(u, v); u /= g; v /= g;
		if(v < 0) u = -u, v = -v;
	}
	bool operator < (const Frac& B)const {
		return u * B.v < v * B.u;
	}
	bool operator == (const Frac& B)const {
		return u * B.v == v * B.u;
	}
	Frac(ll u = 0, ll v = 1) : u(u), v(v) {calc();}
}lsh[MAXN];
struct Qry {
	ll a, b, c;
	char opt;
}q[MAXN];
int tot, n, num[MAXN], vis[MAXN], idx;
void LSH() {
	sort(lsh + 1, lsh + 1 + tot);
	tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(Frac a) {
	return lower_bound(lsh + 1, lsh + 1 + tot, a) - lsh;
}
struct BIT {
	int t[MAXN];
	void add(int i, int k) {
		for(; i <= tot; i += i & -i) t[i] += k;
	}
	void add(int x, int y, int k) {
		add(x, k); add(y+1, -k);
	}
	int sum(int i) {
		int ans = 0;
		for(; i; i -= i & -i) ans += t[i];
		return ans;
	}
}tr;
void ADNode(int i, int v) {
	Qry now = q[i];
	if(now.a == 0) {
		if(now.b > now.c) tr.add(1, tot, v);
	} else {
		int pos = LSH(Frac(now.c - now.b, now.a));
		if(now.a > 0) tr.add(pos+1, tot, v);
		else tr.add(1, pos-1, v);
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		q[i].opt = readc(); q[i].a = read();
		if(q[i].opt == 'A') {
			q[i].b = read(); q[i].c = read();
			num[++idx] = i;
			if(q[i].a != 0) lsh[++tot] = Frac(q[i].c - q[i].b, q[i].a);
		} else if(q[i].opt == 'Q') {
			lsh[++tot] = Frac(q[i].a, 1);
		}
	}
	LSH();
	for(int i = 1; i <= n; i++) {
		if(q[i].opt == 'A') {
			ADNode(i, 1);
		} else if(q[i].opt == 'D') {
			if(vis[q[i].a]) continue;
			vis[q[i].a] = 1;
			ADNode(num[q[i].a], -1);
		} else {
			printf("%d\n", tr.sum(LSH(Frac(q[i].a, 1))));
		}
	}
	return 0;	
}
