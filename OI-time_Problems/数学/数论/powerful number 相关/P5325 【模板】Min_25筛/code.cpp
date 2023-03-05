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
const int MAXK = 5e6 + 5;
const int P = 1e9 + 7, inv6 = 166666668;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll n, g[MAXK], sg[MAXK], tb_g[MAXK];
int pr[MAXK], ip[MAXK], tot; 
void Sieve(int n) {
	ip[1] = 1; g[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			g[i] = i-1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j]) g[k] = g[i] * (pr[j] - 1);
			else {
				g[k] = g[i] * pr[j];
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) g[i] = mul(g[i], i);
	for(int i = 1; i <= n; i++) sg[i] = pls(sg[i-1], g[i]);
}
ll S1(ll n) {n %= P; return n * (n + 1) / 2 % P;}
ll S2(ll n) {n %= P; return n * (n + 1) % P * (n + n + 1) % P * inv6 % P;}
ll calcsg(ll x) {
	if(x < MAXK) return sg[x];
	if(~tb_g[n / x]) return tb_g[n / x];
	ll ret = S2(x);
	for(ll i = 2, j; i <= x; i = j + 1) {
		ll t = x / i; j = x / t;
		ret = mns(ret, mul(calcsg(t), mns(S1(j), S1(i-1))));
	}
	return tb_g[n / x] = ret;
}
ll calch(ll p, ll pk, ll e) {p %= P; pk %= P; e %= P; return (e-1) * (p-1) % P * pk % P;}
ll dfs(ll k, ll lst, ll h) {
	ll ans = mul(h, calcsg(n / lst));
	for(ll g = n / lst; 1ll * pr[k] * pr[k] <= g; k++) {
		for(ll e = 2, p = 1ll * pr[k] * pr[k]; p <= g; p *= pr[k], e++)
			ans = pls(ans, dfs(k+1, lst * p, mul(h, calch(pr[k], p, e))));
	}
	return ans;
}
int main() {
	n = read();
	Sieve(MAXK - 1);
	memset(tb_g, -1, sizeof tb_g);
	printf("%lld\n", dfs(1, 1, 1));
	return 0;
}
