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
const int MAXN = 1e9 + 5, MAXR = 1e6 + 5;
const int P = 1e9 + 7;
int n;
ll mu[MAXR], pr[MAXR], tot, ip[MAXR];
void init() {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i < MAXR; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] < MAXR; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				mu[i * pr[j]] = -mu[i];
			} else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i < MAXR; i++) mu[i] += mu[i-1];
}
ll smu[MAXN / MAXR], vmu[MAXN / MAXR];
ll Smu(int x) {
	if(x < MAXR) return mu[x] % P;
	if(vmu[n / x]) return smu[n / x];
	vmu[n / x] = 1;
	ll ans = 1;
	for(int i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);
		ans = (ans - (j - i + 1) * Smu(x / i)) % P;
	}
	return smu[n / x] = ans;
}
ll calc(int n) {
	ll ans = 0;
	for(int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ans = (ans + 1ll * (j - i + 1) * (n / i)) % P;
	}
	return ans;
}

int main() {
	init();
	n = read();
	ll ans = 0;
	for(int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ll tmp = calc(n / i);
		ans = (ans + tmp * tmp % P * (Smu(j) - Smu(i-1))) % P;
	}
	printf("%lld\n", (ans % P + P) % P);
	return 0;
}
