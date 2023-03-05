#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
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
#define mp make_pair
const int MAXN = 1e9+5, XN = 1e6+5;
const int MAXK = 2e3+5;
int n, m, K, ip[XN], pr[XN], tot, pK[100], totK;
ll mu[XN], smu0[XN];
void init(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {pr[++tot] = i; mu[i] = -1;}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				mu[i * pr[j]] = -mu[i];
			} else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) smu0[i] = smu0[i-1] + mu[i];
}
ll calcsmu(ll n) {
	if(n < XN) return smu0[n];
	static map<ll, ll> table;
	map<ll, ll>::iterator it;
	if((it = table.find(n)) != table.end()) return it->second;
	ll ret = 1;
	for(ll i = 2, j; i <= n; i = j+1) {
		j = n / (n / i);
		ret -= (j - i + 1) * calcsmu(n / i);
	}
	table[n] = ret;
	return ret;
}
ll calcf(ll n, int k) {
	if(n == 0) return 0;
	if(k == 0) return n;
	static map<pair<ll, int>, ll> table;
	map<pair<ll, int>, ll>::iterator it;
	if((it = table.find(mp(n, k))) != table.end()) return it->second;
	ll ret = calcf(n, k-1) - calcf(n / pK[k], k-1);
	table[mp(n, k)] = ret;
	return ret;
}
ll calcg(ll n, int k) {
	if(n == 0) return 0;
	if(k == 0) return calcsmu(n);
	static map<pair<ll, int>, ll> table;
	map<pair<ll, int>, ll>::iterator it;
	if((it = table.find(mp(n, k))) != table.end()) return it->second;
	ll ret = calcg(n, k-1) + calcg(n / pK[k], k);
	table[mp(n, k)] = ret;
	return ret;
}
int main() {
	init(XN-1);
	n = read(), m = read(), K = read();
	int t = K;
	for(int i = 2; i * i <= t; i++)
		if(t % i == 0) {
			pK[++totK] = i;
			while(t % i == 0) t /= i;
		}
	if(t > 1) pK[++totK] = t;
	ll ret = 0;
	for(ll i = 1, j; i <= n && i <= m; i = j+1) {
		j = min(n / (n / i), m / (m / i));
		ret += (calcg(j, totK) - calcg(i-1, totK)) * (n / i) * calcf(m / i, totK);
	}
	printf("%lld\n", ret);
	return 0;
}
