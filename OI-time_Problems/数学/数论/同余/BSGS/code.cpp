#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
int P, a, b, B;
int qpow(int a, int n=P-2) {int ret = 1; for(; n; n >>= 1, a = 1ll * a * a % P) if(n & 1) ret = 1ll * ret * a % P; return ret;}
map<int, int> mp;
int main() {
	P = read(), a = read(), b = read();
	while(1ll * B * B <= P) B++;
	int t = qpow(a), pro = 1;
	for(int i = 0; i < B; i++) {
		if(!mp.count(1ll * pro * b % P)) mp[1ll * pro * b % P] = i;
		pro = 1ll * pro * t % P;
	}
	t = qpow(a, B); pro = 1;
	for(int i = 0; i < B; i++) {
		if(mp.count(pro)) {
			printf("%d\n", i * B + mp[pro]);
			return 0;
		}
		pro = 1ll * pro * t % P;
	}
	printf("no solution\n");
	return 0;
}
