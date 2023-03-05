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
const ll MAXN = 1e10 + 5, PN = 1.7e6;
int ip[PN+5], tot;
int mu[PN+5], phi[PN+5], pr[PN+5];
ll smu[PN + 5], sphi[PN + 5];
map<int, ll> fmu, fphi;
void init(ll n) {
	ip[1] = 1; mu[1] = phi[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
			phi[i] = i-1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			int k = pr[j] * i;
			ip[k] = 1;
			if(i % pr[j]) {
				mu[k] = -mu[i];
				phi[k] = phi[i] * (pr[j] - 1);
			} else {
				mu[k] = 0;
				phi[k] = phi[i] * pr[j];
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) sphi[i] = sphi[i-1] + phi[i], smu[i] = smu[i-1] + mu[i];
}
ll calcphi(ll x) {
	if(x <= PN) return sphi[x];
	if(fphi.count(x)) return fphi[x];
	ll ans = 1ull * x * (1ull * x + 1) / 2;
	for(ll i = 2, j; i <= x; i = j+1) {
		j = x / (x/i);
		ans -= 1ll * (j - i + 1) * calcphi(x/i);
	}
	return fphi[x] = ans;
}
ll calcmu(ll x) {
	if(x <= PN) return smu[x];
	if(fmu.count(x)) return fmu[x];
	ll ans = 1;
	for(ll i = 2, j; i <= x; i = j+1) {
		j = x / (x/i);
		ans -= 1ll * (j - i + 1) * calcmu(x/i);
	}
	return fmu[x] = ans;
}
int main() {
	init(PN);
	int T = read();
	for(int i = 1; i <= T; i++) {
		int n = read();
		printf("%lld %lld\n", calcphi(n), calcmu(n));
	}
	return 0;
}
