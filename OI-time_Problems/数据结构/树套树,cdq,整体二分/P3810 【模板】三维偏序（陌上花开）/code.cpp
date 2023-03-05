#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
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
const int MAXN = 1e5 + 5;
const int MAXK = 2e5 + 5;
int n, K;
namespace Treap {
	const int MAXNODE = 3e6 + 5;
	struct Node{int ls, rs, v, s, c, k;}e[MAXNODE];
	int tot;
	void upd(int p) {e[p].s = e[e[p].ls].s + e[e[p].rs].s + e[p].c;}
	void lturn(int& p) {int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(s); p = s;}
	void rturn(int& p) {int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(s); p = s;}
	void ins(int& p, int v) {
		if(!p) e[p = ++tot] = (Node){0, 0, v, 1, 1, rand()};
		else if(e[p].v == v) e[p].c++, upd(p);
		else if(e[p].v > v)
			ins(e[p].ls, v), e[p].k > e[e[p].ls].k ? rturn(p) : upd(p);
		else 
			ins(e[p].rs, v), e[p].k > e[e[p].rs].k ? lturn(p) : upd(p);
	}
	int leq(int p, int v) {
		if(!p) return 0;
		else if(e[p].v == v) return e[e[p].ls].s + e[p].c;
		else if(e[p].v > v) return leq(e[p].ls, v);
		else return e[e[p].ls].s + e[p].c + leq(e[p].rs, v);
	}
}
namespace BIT {
	int rt[MAXK];
	void add(int i, int v) {for(; i <= K; i += i&-i) Treap::ins(rt[i], v);}
	int sum(int i, int v) {int ret = 0; for(; i; i -= i&-i) ret += Treap::leq(rt[i], v); return ret;}
}
struct Item {int k, a, b, c;}q[MAXN * 2];
int tot, ans[MAXN], f[MAXN];
bool cmp(const Item& A, const Item& B) {
	if(A.a != B.a) return A.a < B.a;
	return A.k < B.k;
}
int main() {
	srand(time(0));
	n = read(); K = read();
	for(int i = 1; i <= n; i++) {
		int a = read(), b = read(), c = read();
		q[++tot] = (Item){0, a, b, c};
		q[++tot] = (Item){i, a, b, c};
	}
	sort(q + 1, q + 1 + tot, cmp);
	for(int i = 1; i <= tot; i++) {
		Item t = q[i];
		if(t.k == 0) {
			BIT::add(t.b, t.c);
		} else {
			ans[t.k] = BIT::sum(t.b, t.c);
		}
	}
	for(int i = 1; i <= n; i++) f[ans[i]-1]++;
	for(int i = 0; i < n; i++) printf("%d\n", f[i]);
	return 0;
}
