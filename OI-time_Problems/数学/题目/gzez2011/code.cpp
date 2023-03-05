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
const int MAXN = 1e9 + 5, MAXSN = 2e5 + 5;
int pr[MAXSN], ip[MAXSN], tot, mu[MAXSN];
void init() {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i < MAXSN; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] < MAXSN; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				mu[i * pr[j]] = -mu[i];
			} else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
}
bool check(int n, int k) {
	ll ans = 0;
	for(int i = 1; 1ll * i * i <= n; i++)
		ans += mu[i] * (n / i / i);
	return ans >= k;
}
int main() {
	init();
	int T = read();
	while(T--) {
		int K = read();
		int l = K, r = 1644934081,ans;
		while(l <= r) {
			int m = ((ll)l + r) >> 1;
			if(check(m, K)) {ans = m; r = m - 1;}
			else l = m + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
