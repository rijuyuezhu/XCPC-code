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
const int MAXN = 1e6 + 5;
int ip[MAXN], pr[MAXN], tot, phi[MAXN], havert[MAXN], fj[MAXN], cnt, ans[MAXN], anscnt;
void init() {
	ip[1] = 1; phi[1] = 1;
	for(int i = 2; i < MAXN; i++) {
		if(!ip[i]) {pr[++tot] = i; phi[i] = i - 1;}
		for(int j = 1; j <= tot && 1ll * i * pr[j] < MAXN; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) phi[i * pr[j]] = phi[i] * (pr[j] - 1);
			else {
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
		}
	}
	havert[2] = havert[4] = 1;
	for(int j = 2; j <= tot; j++) {
		for(int i = 1; 1ll * i * pr[j] < MAXN; i *= pr[j]) havert[i * pr[j]] = 1;
		for(int i = 2; 1ll * i * pr[j] < MAXN; i *= pr[j]) havert[i * pr[j]] = 1;
	}
}
int ksm(int a, int n, int mod) {
	int ret = 1;
	for(; n; n >>= 1, a = 1ll * a * a % mod)
		if(n & 1) ret = 1ll * ret * a % mod;
	return ret;
}
void fenjie(int n) {
	cnt = 0;
	for(int i = 2; i * i <= n; i++)
		if(n % i == 0) {
			fj[++cnt] = i;
			while(n % i == 0) n /= i;
		}
	if(n > 1) fj[++cnt] = n;
}
bool check(int n, int g) {
	if(ksm(g, phi[n], n) != 1) return 0;
	for(int i = 1; i <= cnt; i++)
		if(ksm(g, phi[n] / fj[i], n) == 1) return 0;
	return 1;
}
int getrt(int n) {
	for(int i = 1; i < n; i++)
		if(check(n, i)) return i;
	return 0;
}
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
void getallrt(int n, int g) {
	anscnt = 0;
	int k = 1;
	for(int i = 1, k = g; i <= phi[n]; i++, k = 1ll * k * g % n)//be careful, i <= phi[n]!!!(when n=2)
		if(gcd(i, phi[n]) == 1) ans[++anscnt] = k;
}
void work() {
	int n = read(), d = read();
	if(!havert[n]) {
		printf("0\n\n");
		return ;
	}
	fenjie(phi[n]);
	int g = getrt(n);
	getallrt(n, g);
	sort(ans + 1, ans + 1 + anscnt);
	printf("%d\n", anscnt);
	for(int i = d; i <= anscnt; i += d) printf("%d ", ans[i]);
	printf("\n");
}
int main() {
	init();
	int T = read();
	while(T--) work();
	return 0;
}
