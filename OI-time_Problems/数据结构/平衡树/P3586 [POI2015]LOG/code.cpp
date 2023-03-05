#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<queue>
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
	for(; ch != 'U' && ch != 'Z'; ch = getchar());
	return ch;
}
const int MAXN = 1e6 + 5;
namespace Treap {
#define L e[x].ls
#define R e[x].rs
	struct Node {
		int ls, rs, key, siz;
		ll val, sum;
	}e[MAXN];
	queue<int> dsb;
	int cnt, rt;
	void upd(int x) {
		e[x].sum = e[L].sum + e[R].sum + e[x].val;
		e[x].siz = e[L].siz + e[R].siz + 1;
	}
	void lturn(int& x) {int s = e[x].rs; e[x].rs = e[s].ls; upd(x); e[s].ls = x; upd(s); x = s;}
	void rturn(int& x) {int s = e[x].ls; e[x].ls = e[s].rs; upd(x); e[s].rs = x; upd(s); x = s;}
	int cre() {
		if(dsb.empty()) return ++cnt;
		int x = dsb.front(); dsb.pop();
		return x;
	}
	void ins(ll v, int& x) {
		if(!x) e[x = cre()] = (Node){0, 0, rand(), 1, v, v};
		else if(v <= e[x].val)
			ins(v, L), e[L].key < e[x].key ? rturn(x) : upd(x);
		else 
			ins(v, R), e[R].key < e[x].key ? lturn(x) : upd(x);
	}
	void del(ll v, int& x) {
		if(v < e[x].val) del(v, L), upd(x);
		else if(v > e[x].val) del(v, R), upd(x);
		else if(!L) dsb.push(x), x = R;
		else if(!R) dsb.push(x), x = L;
		else if(e[L].key < e[R].key)
			rturn(x), del(v, R), upd(x);
		else 
			lturn(x), del(v, L), upd(x);
	}
	ll getsum(ll v, int x) {
		if(!x) return 0;
		else if(e[x].val <= v) return e[L].sum + e[x].val + getsum(v, R);
		else return getsum(v, L);
	}
	int getsiz(ll v, int x) {
		if(!x) return 0;
		else if(e[x].val <= v) return e[L].siz + 1 + getsiz(v, R);
		else return getsiz(v, L);
	}
#undef L
#undef R
}
using namespace Treap;
int n, m;
ll a[MAXN];
int main() {
	srand(time(0));
	n = read(), m = read();
	for(int i = 1; i <= n; i++) ins(0, rt);
	for(int i = 1; i <= m; i++) {
		char opt = readc();
		if(opt == 'U') {
			int k = read(); ll t = read();
			del(a[k], rt); a[k] = t; ins(a[k], rt);
		} else {
			int c = read(), s = read();
			int ans = (e[rt].siz - getsiz(s-1, rt)) + getsum(s-1, rt) / s;
			if(ans >= c) printf("TAK\n");
			else printf("NIE\n");
		}
	}
	return 0;
}
