#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
const int SN = (1 << 16) + 5;
ll n, pr[SN], ip[SN], tot;
ll ans;
void getpr(int n) {
	ip[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) pr[++tot] = i;
		for(int j = 1; j <= tot && i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
ll phi(ll k) {
	ll ans = k;
	for(int j = 1; j <= tot && pr[j] * pr[j] <= k; j++)
		if(k % pr[j] == 0) {
			ans = ans / pr[j] * (pr[j] - 1);
			while(k % pr[j] == 0) k /= pr[j];
		}
	if(k > 1) ans = ans / k * (k - 1);
	return ans;
}
void calc(ll d) {
	ans += d * phi(n / d);
}
int main() {
	n = read();	
	getpr((int)sqrt(n) + 5);
	for(int i = 1; 1ll * i * i <= n; i++)
		if(n % i == 0) {
			calc(i);
			if(i * i != n) calc(n / i);
		}
	printf("%lld\n", ans);
	return 0;
}
