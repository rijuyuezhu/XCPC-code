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
const int MAXN = 1e7 + 5;
const int P = 1e8 + 9;
ll f(ll x) {
	return x * (x + 1) / 2 % P;
}
int g[MAXN], pr[MAXN], tot;
bool ip[MAXN];
void init() {
	ip[1] = 1; g[1] = 1;
	for(int i = 2; i < MAXN; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			g[i] = (1ll * i - 1ll * i * i) % P;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] < MAXN; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				g[i * pr[j]] = 1ll * g[i] * g[pr[j]] % P;
			} else {
				g[i * pr[j]] = 1ll * g[i] * pr[j] % P;
				break;
			}
		}
	}
	for(int i = 1; i < MAXN; i++) g[i] = (g[i-1] + g[i]) % P;
}

int main() {
	init();
	int t = read();
	while(t--) {
		int n = read(), m = read();
		int ans = 0;
		for(int i = 1, j; i <= n && i <= m; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
			ans = (ans + 1ll * f(n / i) * f(m / i) % P * (g[j] - g[i-1]) % P) % P;
		}
		printf("%d\n", (ans % P + P) % P);
	}
	return 0;
}
