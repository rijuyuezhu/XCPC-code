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
const int P = 998244353;
const int MAXN = 2e3 + 5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, k, x[MAXN], y[MAXN];
int calc(int k) {
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int s1 = 1, s2 = 1;
		for(int j = 1; j <= n; j++) if(i != j)
			s1 = mul(s1, mns(k, x[j])), s2 = mul(s2, mns(x[i], x[j]));
		ans = pls(ans, mul(y[i], mul(s1, qpow(s2, P-2))));
	}
	return ans;
}
int main() {
	n = read(); k = read();
	for(int i = 1; i <= n; i++) x[i] = read(), y[i] = read();
	printf("%d\n", calc(k));
	return 0;
}
