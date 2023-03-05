#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int P = 1e9 + 7, MAXN = 1e5 + 5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, pr[MAXN], tot, ip[MAXN], mu[MAXN], inv[MAXN], f[MAXN], F[MAXN];
vector<int> fct[MAXN];
void init(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {pr[++tot] = i; mu[i] = mns(0, 1);}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) mu[i * pr[j]] = mns(0, mu[i]);
			else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) 
		for(int j = i; j <= n; j += i)
			fct[j].push_back(i);
	inv[1] = 1; for(int i = 2; i <= n; i++) inv[i] = mul(P - P/i, inv[P % i]);
}
int main() {
	n = read();
	init(n);
	for(int i = 2; i <= n; i++) {
		for(vector<int>::iterator p = fct[i].begin(); p != fct[i].end(); p++)
			f[i] = pls(f[i], mul(n / *p, F[*p]));
		f[i] = mul(pls(f[i], n), inv[n - n / i]);
		for(int j = 1; j <= n / i; j++)
			F[i * j] = pls(F[i * j], mul(f[i], mu[j]));
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = pls(ans, f[i]);
	ans = pls(1, mul(ans, inv[n]));
	printf("%d\n", ans);
	return 0;
}
