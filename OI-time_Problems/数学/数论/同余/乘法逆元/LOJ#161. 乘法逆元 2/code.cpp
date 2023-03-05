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
const int MAXN = 5000005;
const int P = 1e9 + 7;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a - b + P : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
int n;
ll a[MAXN], s[MAXN], sv[MAXN], av[MAXN];
void exgcd(ll a, ll b, ll& x, ll& y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a) {
	ll x, y;
	exgcd(a, P, x, y);
	return (x % P + P) % P;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	s[0] = 1;
	for(int i = 1; i <= n; i++) s[i] = mul(s[i-1], a[i]);
	sv[n] = inv(s[n]);
	for(int i = n-1; i >= 1; i--) sv[i] = mul(sv[i+1], a[i+1]);
	for(int i = 1; i <= n; i++) av[i] = mul(s[i-1], sv[i]);
	ll ans = 0, bas = 998244353, k = 1;
	for(int i = n; i >= 1; i--, k = mul(k, bas))
		ans = pls(ans, mul(av[i], k));
	printf("%lld\n", ans);
	return 0;
}
