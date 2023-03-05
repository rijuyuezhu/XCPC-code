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
int n;
ll r[MAXN], m[MAXN], ansr, ansm;
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
void exgcd(ll a, ll b, ll& x, ll& y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll qmul(ll a, ll b, ll mod) {
	ll ret = 0;
	for(; b; b >>= 1, (a += a) %= mod)
		if(b & 1) (ret += a) %= mod;
	return ret;
}
ll calc(ll a, ll b, ll c) {
	ll g = gcd(a, b); a /= g; b /= g; c /= g;
	ll x, y; exgcd(a, b, x, y); x = qmul(x, c, b);
	return (x % b + b) % b;
}
void solve() {
	ansr = r[1], ansm = m[1];
	for(int i = 2; i <= n; i++) {
		ll k = calc(ansm, m[i], (r[i] - ansr) % m[i] + m[i]), m1 = ansm;
		ansm = m1 / gcd(m1, m[i]) * m[i];
		(ansr += qmul(k, m1, ansm)) %= ansm;
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) m[i] = read(), r[i] = read();
	solve();
	printf("%lld\n", ansr);
	return 0;
}
