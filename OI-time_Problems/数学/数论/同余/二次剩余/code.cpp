#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
ll n;
ll P, a, I2;
struct F2 {ll x, y;};
F2 operator * (const F2& A, const F2& B) {return (F2){A.x * B.x % P + I2 * (A.y * B.y % P) % P, (A.x * B.y + A.y * B.x) % P};}
ll qpow(ll a, int n) {ll ret = 1; for(; n; n >>= 1, a = a * a % P) if(n & 1) ret = ret * a % P; return ret;}
F2 qpow(F2 a, int n) {F2 ret = (F2){1, 0}; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
ll judge(ll a) {return qpow(a, (P-1) / 2);}
void work() {
	n = read(); P = read();
	ll k = judge(n);
	if(k == 0) {
		printf("0\n");
		return ;
	} else if(k == P-1) {
		printf("Hola!\n");
		return ;
	}
	while(1) {
		a = rand() % P;
		I2 = (a * a % P + P - n) % P;
		if(judge(I2) == P-1) break;
	}
	ll ans1 = qpow((F2){a, 1}, (P+1) / 2).x % P;
	ll ans2 = P-ans1;
	if(ans1 > ans2) swap(ans1, ans2);
	printf("%lld %lld\n", ans1, ans2);
}
	

int main() {
	int T = read();
	while(T--) work();
	return 0;
}
