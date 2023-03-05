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
const int P = 1e9 + 7;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
const int MAXK = 1e6 + 5;
int n, k, fac[MAXK], ifac[MAXK], lv[MAXK], rv[MAXK];
int y[MAXK];
int main() {
	n = read(), k = read();
	for(int i = 1; i <= k+2; i++) y[i] = pls(y[i-1], qpow(i, k));
	k += 2;
	fac[0] = 1; for(int i = 1; i <= k; i++) fac[i] = mul(fac[i-1], i);
	ifac[k] = qpow(fac[k], P-2);
	for(int i = k-1; i >= 0; i--) ifac[i] = mul(ifac[i+1], i+1);
	lv[0] = rv[k+1] = 1;
	for(int i = 1; i <= k; i++) lv[i] = mul(lv[i-1], mns(n, i));
	for(int i = k; i >= 1; i--) rv[i] = mul(rv[i+1], mns(n, i));
	int ans = 0;
	for(int i = 1; i <= k; i++) {
		ans = (1ll * ans + 1ll * y[i] * lv[i-1] % P * rv[i+1] % P * ifac[i-1] % P * ((k-i) & 1 ? P - ifac[k-i] : ifac[k-i])) % P;
	}
	printf("%d\n", ans);
	return 0;
}
