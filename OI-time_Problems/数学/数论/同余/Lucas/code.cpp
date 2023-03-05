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

const int MAXN = 2e5 + 5;
int n, m, p;
int pls(int a, int b) {return a + b < p ? a + b : a + b - p;}
int mns(int a, int b) {return a < b ? a + p - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % p;}
int qpow(int a, int n) {
	int ret = 1;
	for(; n; n >>= 1, a = mul(a, a))
		if(n & 1) ret = mul(ret, a);
	return ret;
}
int fac[MAXN], inv[MAXN];
int C(int n, int m) {//n,m < p
	if(n < 0 || m < 0 || m > n) return 0;
	return mul(mul(fac[n], inv[m]), inv[n-m]);
}
int Lucas(int n, int m) {
	return !m ? 1 : mul(C(n % p, m % p), Lucas(n / p, m / p));
}
void work() {
	n = read(), m = read(), p = read();
	memset(fac, 0x00, sizeof fac);
	memset(inv, 0x00, sizeof inv);
	fac[0] = 1;
	for(int i = 1; i < p; i++) fac[i] = mul(fac[i-1], i);
	inv[p-1] = qpow(fac[p-1], p-2);
	for(int i = p-2; i >= 0; i--) inv[i] = mul(inv[i+1], i+1);
	printf("%d\n", Lucas(n+m, n));

}
int main() {
	int T = read();
	while(T--) {
		work();
	}
	return 0;
}
