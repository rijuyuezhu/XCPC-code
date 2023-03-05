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
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return mint(MOD(a.v + b.v));}
mint operator - (mint a, mint b) {return mint(MOD(a.v - b.v + P));}
mint operator * (mint a, mint b) {return mint(MOD(1ll * a.v * b.v % P));}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
mint inv(mint a) {return qpow(a, P-2);}
int n;
int phi(int n) {
	int ret = n;
	for(int i = 2; 1ll * i * i <= n; i++)
		if(n % i == 0) {
			ret = ret / i * (i-1);
			while(n % i == 0) n /= i;
		}
	if(n > 1) ret = ret / n * (n-1);
	return ret;
}

int main() {
	for(int t = read(); t; t--) {
		n = read();
		mint ans = 0;
		for(int i = 2; 1ll * i * i <= n; i++) 
			if(n % i == 0) {
				ans = ans + mint(phi(i)) * qpow(n, n / i);
				if(i * i != n) {
					ans = ans + mint(phi(n / i)) * qpow(n, i);
				}
			}
		printf("%d\n", (ans * inv(n)).v);
	}
	return 0;
}
