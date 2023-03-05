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
const int P = 20101009;
const int MAXN = 1e7 + 5;
int mul(int a, int b) {return 1ll * a * b % P;}
int n, m;
int g[MAXN], pr[MAXN], ip[MAXN], tot;
void pre_gao(int n) {
	ip[1] = 1; g[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i; g[i] = -1;
		}
		for(int j = 1; j <= tot && 1ll * pr[j] * i <= n; j++) {
			ip[pr[j] * i] = 1;
			if(i % pr[j]) g[pr[j] * i] = -g[i];
			else {
				g[pr[j] * i] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) (g[i] *= 1ll * i * i % P) %= P;
	for(int i = 1; i <= n; i++) (g[i] += g[i-1]) %= P;
}
int S2(int n) {return 1ll * n * (n+1) / 2 % P;}
int S1(int n, int m) {
	int ans = 0;
	for(int i = 1, j; i <= n && i <= m; i = j+1) {
		j = min(n / (n/i), m / (m/i));
		(ans += 1ll * (1ll * g[j] - g[i-1]) % P * S2(n / i) % P * S2(m / i) % P) %= P;
	}
	return ans;
}
int main() {
	n = read(), m = read();
	pre_gao(min(n, m));
	int ans = 0;
	for(int i = 1, j; i <= n && i <= m; i = j+1) {
		j = min(n / (n/i), m / (m/i));
		(ans += 1ll * (1ll * S2(j) - S2(i-1)) % P * S1(n / i, m / i) % P) %= P;
	}
	printf("%d\n", (ans % P + P) % P);
	return 0;
}
