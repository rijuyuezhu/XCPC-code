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
const int MAXN = 5e4 + 5;
int k;

int ip[MAXN], pr[MAXN], tot;
int mu[MAXN];
void init(int n) {
	ip[0] = ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
		}
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
	for(int i = 1; i <= n; i++) 
		mu[i] += mu[i - 1];
}


int f(int n, int m) {
	n /= k, m /= k;
	int ans = 0;
	for(int i = 1, j; i <= n && i <= m; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		ans += 	(n / i) * (m / i) * (mu[j] - mu[i - 1]);
	}
	return ans;
}
int main() {
	init(MAXN - 1);
	int n = read();
	while(n--) {
		int a = read(), b = read(), c = read(), d = read();
		k = read();
		printf("%d\n", f(b, d) - f(a - 1,  d) - f(b, c - 1) + f(a - 1, c - 1));
	}
	return 0;
}
