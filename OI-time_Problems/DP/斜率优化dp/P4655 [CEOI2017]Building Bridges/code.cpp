#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
typedef long double ld;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
void chkmin(ll& x, ll y) {x = min(x, y);}
const int MAXN = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, h[MAXN], w[MAXN], hd, tl, que[MAXN];
ll dp[MAXN], S[MAXN];
struct Item {int id, x, k; ll y;}a[MAXN], tmp[MAXN];
bool cmpk(const Item& a, const Item& b) {return a.k < b.k;}
bool cmpx(const Item& a, const Item& b) {return a.x < b.x;}
int X(int i) {return a[i].x;}
ll Y(int i) {return a[i].y;}
ld slope(int i, int j) {return X(i) == X(j) ? (Y(i) <= Y(j) ? 1e40 : -1e40) : ld(Y(j)-Y(i)) / (X(j)-X(i));}
void cdq(int l, int r) {
	if(l == r) { a[l].y = dp[a[l].id] + 1ll * h[a[l].id] * h[a[l].id] - S[a[l].id]; return ;}
	int m = (l + r) >> 1;
	int p, p1 = l, p2 = m+1;
	for(int i = l; i <= r; i++) 
		if(a[i].id <= m) tmp[p1++] = a[i];
		else tmp[p2++] = a[i];
	for(int i = l; i <= r; i++) a[i] = tmp[i];
	cdq(l, m);
	hd = 1; tl = 0;
	for(int i = l; i <= m; i++) {
		while(hd < tl && slope(que[tl-1], que[tl]) >= slope(que[tl], i)) --tl;
		que[++tl] = i;
	}
	for(int i = m+1; i <= r; i++) {
		while(hd < tl && slope(que[hd], que[hd+1]) <= a[i].k) ++hd;
		if(hd <= tl) {
			int j = que[hd];
			chkmin(dp[a[i].id], dp[a[j].id] + 1ll * (h[a[i].id] - h[a[j].id]) * (h[a[i].id] - h[a[j].id]) + S[a[i].id-1] - S[a[j].id]);
		}
	}
	cdq(m+1, r);
	p = l, p1 = l, p2 = m+1;
	while(p1 <= m && p2 <= r) tmp[p++] = cmpx(a[p1], a[p2]) ? a[p1++] : a[p2++];
	while(p1 <= m) tmp[p++] = a[p1++];
	while(p2 <= r) tmp[p++] = a[p2++];
	for(int i = l; i <= r; i++) a[i] = tmp[i];
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) h[i] = read();
	for(int i = 1; i <= n; i++) S[i] = S[i-1] + (w[i] = read());
	for(int i = 1; i <= n; i++) a[i] = (Item){i, h[i], 2 * h[i], INF}, dp[i] = INF;
	sort(a + 1, a + 1 + n, cmpk);
	dp[1] = 0; cdq(1, n);
	printf("%lld\n", dp[n]);
	return 0;
}
