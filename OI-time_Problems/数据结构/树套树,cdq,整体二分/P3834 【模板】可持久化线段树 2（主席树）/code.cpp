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
const int MAXN = 4e5 + 5;
const int INF = 1e9+5;
struct Item {int k, a, b, c;}q[MAXN], q1[MAXN], q2[MAXN];
int n, m, tot, ans[MAXN];
namespace BIT {
	int t[MAXN];
	int lowbit(int x) {return x&-x;}
	void add(int x, int v) {for(int i = x; i <= n; i += lowbit(i)) t[i] += v;}
	int sum(int x) {int ret = 0; for(int i = x; i; i -= lowbit(i)) ret += t[i]; return ret;}
	int sum(int x, int y) {return sum(y) - sum(x-1);}
}
using namespace BIT;
void solve(int kl, int kr, int l, int r) {
	if(kl > kr) return;
	if(l == r) {
		for(int i = kl; i <= kr; i++) if(q[i].k) ans[q[i].k] = l;
		return ;
	}
	int m = (l + r) >> 1, k1 = 0, k2 = 0;
	for(int i = kl; i <= kr; i++) {
		if(!q[i].k) {
			if(q[i].b <= m) {
				add(q[i].a, 1); q1[++k1] = q[i];
			} else q2[++k2] = q[i];
		} else {
			int t = sum(q[i].a, q[i].b);
			if(q[i].c <= t) q1[++k1] = q[i];
			else {
				q[i].c -= t;
				q2[++k2] = q[i];
			}
		}
	}
	for(int i = 1; i <= k1; i++) if(!q1[i].k) add(q1[i].a, -1);
	for(int i = 1; i <= k1; i++) q[kl+i-1] = q1[i];
	for(int i = 1; i <= k2; i++) q[kl+k1+i-1] = q2[i];
	solve(kl, kl+k1-1, l, m); solve(kl+k1, kr, m+1, r);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		int t = read(); q[++tot] = (Item){0, i, t, 0};
	}
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read(), k = read();
		q[++tot] = (Item){i, l, r, k};
	}
	solve(1, tot, -INF, INF);
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
