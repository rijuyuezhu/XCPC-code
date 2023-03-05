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
const int MAXN = 1e5 + 5;
int n, L[MAXN], R[MAXN], fa[MAXN], stk[MAXN], _stk, ls[MAXN], rs[MAXN], rt;
ll k, H[MAXN], f[MAXN], ans;
bool cmp(int i, int j) {
	if(H[i] != H[j]) return H[i] < H[j];
	return i < j;
}
void dfs(int u) {
	if(!u) return;
	if(ls[u]) {
		L[ls[u]] = L[u]; R[ls[u]] = u - 1; fa[ls[u]] = u;
		dfs(ls[u]);
	}
	if(rs[u]) {
		R[rs[u]] = R[u]; L[rs[u]] = u + 1; fa[rs[u]] = u;
		dfs(rs[u]);
	}
	f[u] = (R[u] - L[u] + 1) * (H[u] - H[fa[u]]);
	if(ls[u]) f[u] += f[ls[u]];
	if(rs[u]) f[u] += f[rs[u]];
	if(f[u] > 0) {//must let f[u] <= 0
		ll cnt = (f[u] - 1) / k + 1;
		ans += cnt, f[u] -= cnt * k;
	}
}
int main() {
	n = read(), k = read();
	for(int i = 1; i <= n; i++) H[i] = read();
	for(int i = 1; i <= n; i++) {
		int cur = _stk;
		while(cur && cmp(i, stk[cur])) cur--;
		if(cur) rs[stk[cur]] = i;
		if(cur < _stk) ls[i] = stk[cur+1];
		stk[_stk = cur+1] = i;
	}
	rt = stk[1];
	L[rt] = 1, R[rt] = n;
	dfs(rt);
	printf("%lld\n", ans);
	return 0;
}
