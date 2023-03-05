#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
int n, B, L[MAXN], R[MAXN], bel[MAXN], num;
ll a[MAXN], tag[MAXN], val[MAXN];
void init() {
	B = sqrt(n) + 1; if(B < 1) B = 1; if(B > n) B = n;
	for(int i = 1; i <= n; i++) {
		bel[i] = (i-1) / B + 1;
		val[bel[i]] += a[i];
	}
	num = (n-1) / B + 1;
	for(int i = 1; i <= num; i++) L[i] = (i-1) * B + 1, R[i] = min(n, i * B);
}
void addbf(int l, int r, ll v) {
	for(int i = l; i <= r; i++) a[i] += v, val[bel[i]] += v;
}
void addwh(int k, ll v) {
	tag[k] += v; val[k] += v * (R[k] - L[k] + 1);
}
void add(int l, int r, ll v) {
	if(bel[l] == bel[r]) {
		addbf(l, r, v);
		return ;
	}
	addbf(l, R[bel[l]], v); addbf(L[bel[r]], r, v);
	for(int i = bel[l] + 1; i <= bel[r] - 1; i++) addwh(i, v);
}
ll sumbf(int l, int r) {
	ll ans = 0;
	for(int i = l; i <= r; i++) ans += a[i] + tag[bel[i]];
	return ans;
}
ll sumwh(int k) {
	return val[k];
}
ll sum(int l, int r) {
	if(bel[l] == bel[r]) return sumbf(l, r);
	ll ans = 0;
	ans += sumbf(l, R[bel[l]]); ans += sumbf(L[bel[r]], r);
	for(int i = bel[l] + 1; i <= bel[r] - 1; i++) ans += sumwh(i);
	return ans;
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	init();
	for(int i = 1; i <= n; i++) {
		int opt = read(), l = read(), r = read(); ll c = read();
		if(opt == 0) add(l, r, c);
		else printf("%lld\n", sum(l, r) % (c+1));
	}
	return 0;
}
