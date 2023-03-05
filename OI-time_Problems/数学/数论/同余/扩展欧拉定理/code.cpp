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
ll a, b, m;
ll phi;
ll qpow(ll a, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, a = a * a % m)
		if(n & 1) ret = ret * a % m;
	return ret;
}
int main() {
	a = read(), m = read();
	phi = m; ll tmp = m;
	for(int i = 2; i * i <= tmp; i++) 
		if(tmp % i == 0) {
			phi = phi / i * (i-1);
			while(tmp % i == 0) tmp /= i;
		}
	if(tmp > 1) phi = phi / tmp * (tmp-1);
	bool flag = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) {
		b = b * 10 + ch - '0';
		if(b >= phi) flag = 1;
		b %= phi;
	}
	printf("%lld\n", qpow(a, b + flag * phi));
	return 0;
}
