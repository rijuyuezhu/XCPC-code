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
const int MAXN = 1e5 + 5, B = 29;
int n, a[MAXN], suma[MAXN], f[MAXN][B+1][2], mxr[MAXN];
int hibit(int x) {
	for(int i = B; i >= 0; i--)
		if((x >> i) & 1) return i;
	return -1;
}
bool check(int l, int r) {
	for(int j = B; j >= 0; j--) {
		if((suma[l-1] >> j) & 1) {
			if(f[r][j][1] - f[l-1][j][1] > 0) return 0;
		} else {
			if(f[r][j][0] - f[l-1][j][0] > 0) return 0;
		}
	}
	return 1;
}
namespace Sgt {
	const int MAXNODE = MAXN << 6;
	struct Node {int ls, rs; ll v, a;} e[MAXNODE];
	int tot;
	void upd(int p, int l, int r) { e[p].v = e[e[p].ls].v + e[e[p].rs].v + e[p].a * (r-l+1); }
	void addrange(int& p, int l, int r, int x, int y, ll val) {
		int pre = p; p = ++tot; e[p] = e[pre];
		if(x == l && y == r) {
			e[p].v += val * (r - l + 1); e[p].a += val;
			return ;
		}
		int m = (l + r) >> 1;
		if(y <= m) addrange(e[p].ls, l, m, x, y, val);
		else if(x > m) addrange(e[p].rs, m+1, r, x, y, val);
		else addrange(e[p].ls, l, m, x, m, val), addrange(e[p].rs, m+1, r, m+1, y, val);
		upd(p, l, r);
	}
	ll query(int p, int l, int r, int x, int y) {
		if(!p) return 0;
		if(x == l && y == r) return e[p].v;
		int m = (l + r) >> 1;
		ll ans = 0;
		if(y <= m) ans = query(e[p].ls, l, m, x, y);
		else if(x > m) ans = query(e[p].rs, m+1, r, x, y);
		else ans = query(e[p].ls, l, m, x, m) + query(e[p].rs, m+1, r, m+1, y);
		return ans + e[p].a * (y - x + 1);
	}
} using namespace Sgt;
int rt[MAXN];
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
		suma[i] = suma[i-1] ^ a[i];
		for(int j = 0; j <= B; j++) f[i][j][0] = f[i-1][j][0], f[i][j][1] = f[i-1][j][1];
		int hi = hibit(a[i]);
		if(hi == -1) continue;
		f[i][hi][(suma[i] >> hi) & 1]++;
	}
	for(int i = 1; i <= n; i++) {
		mxr[i] = -1;
		int l = i, r = n;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(check(i, mid)) {mxr[i] = mid; l = mid + 1;}
			else r = mid - 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		rt[i] = rt[i-1];
		addrange(rt[i], 1, n, i, mxr[i], 1);
	}
	int m = read(); ll lans = 0;
	for(int i = 1; i <= m; i++) {
		int l = (read() + lans) % n + 1, r = (read() + lans) % n + 1;
		if(l > r) swap(l, r);
		printf("%lld\n", lans = query(rt[r], 1, n, l, r) - query(rt[l-1], 1, n, l, r));
	}
	return 0;
}
