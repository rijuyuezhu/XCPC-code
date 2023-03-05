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
int MOD(int a, int p) {return a >= p ? a - p : a;}
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
void exgcd(int a, int b, int& x, int& y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
int inv(int a, int p) {
	int x, y; exgcd(a, p, x, y); return MOD(x % p + p, p);
}
int BSGS(int a, int b, int p) {
	a %= p; b %= p;
	if(!a) return !b ? 1 : -1;
	map<int, int> mp;
	int B = 0; while(1ll * B * B <= p) B++;
	int t = inv(a, p), pro = 1;
	for(int i = 0; i < B; i++) {
		if(!mp.count(1ll * pro * b % p)) mp[1ll * pro * b % p] = i;
		pro = 1ll * pro * t % p;
	}
	t = inv(pro, p); pro = 1;
	for(int i = 0; i < B; i++) {
		if(mp.count(pro)) return i * B + mp[pro];
		pro = 1ll * pro * t % p;
	}
	return -1;
}
int ExBSGS(int a, int b, int p) {
	a %= p; b %= p;
	if(b == 1 || p == 1) return 0;
	if(!a) return !b ? 1 : -1;
	int cnt = 0, pro = 1;
	while(1) {
		int d = gcd(a, p);
		if(d == 1) break;
		if(b % d) return -1;
		b /= d; p /= d; pro = 1ll * pro * (a / d) % p; ++cnt;
		if(pro == b) return cnt;
	}
	int ret = BSGS(a % p, 1ll * b * inv(pro, p) % p, p);
	if(ret == -1) return -1;
	return ret + cnt;
}
int main() {
	int a, p, b;
	while(1) {
		a = read(), p = read(), b = read();
		if(!a) return 0;
		int ans = ExBSGS(a, b, p);
		if(ans == -1) printf("No Solution\n");
		else printf("%d\n", ans);
	}
	return 0;
}
