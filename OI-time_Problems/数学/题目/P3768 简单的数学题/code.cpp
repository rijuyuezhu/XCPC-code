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
const ll MAXN = 1e10 + 5;
const int MAXR = 5e6 + 5;
ll P, n, inv6, f[MAXR];
int pr[MAXR], ip[MAXR], tot;
bool vis[MAXN / MAXR];
ll sf[MAXN / MAXR];

void exgcd(ll a, ll b, ll& x, ll& y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a) {
	ll x, y;
	exgcd(a, P, x, y);
	return (x % P + P) % P;
}

void init() {
	inv6 = inv(6);
	
	ip[0] = ip[1] = 1; f[1] = 1;
	for(int i = 2; i < MAXR; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			f[i] = i - 1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] < MAXR; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) f[i * pr[j]] = f[i] * (pr[j] - 1) % P;
			else {
				f[i * pr[j]] = f[i] * pr[j] % P;
				break;
			}
		}
	}
	for(int i = 1; i < MAXR; i++) 
		f[i] = f[i] * i % P * i % P;
	for(int i = 1; i < MAXR; i++)
		f[i] = (f[i] + f[i-1]) % P;
}

ll g(ll x) {
	ll t = x * (x + 1) / 2 % P;
	return t * t % P;
}
ll sx2(ll x) {
	x %= P;
	return x * (x + 1) % P * (2 * x + 1) % P * inv6 % P;
}

ll SF(ll x) {
	if(x < MAXR) return f[x];
	if(vis[n / x]) return sf[n / x];
	vis[n / x] = 1;
	ll res = g(x);
	for(ll i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);
		res = (res - SF(x / i) * ((sx2(j) - sx2(i-1) + P) % P) % P + P) % P;
	}
	return sf[n / x] = res;
}
int main() {
	P = read(), n = read();
	init();
	ll ans = 0;
	for(ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ans = (ans + g(n / i) * ((SF(j) - SF(i-1) + P) % P) % P) % P;
	}
	printf("%lld\n", ans);
	return 0;
}
