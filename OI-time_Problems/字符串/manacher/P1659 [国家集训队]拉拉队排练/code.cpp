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
char readc() {
	char ch = getchar();
	for(; ch < 'a' || ch > 'z'; ch = getchar());
	return ch;
}
const int MAXN = 1e6 + 5;
const int P = 19930726;
int n, r[MAXN];
char s[MAXN];
ll K, t[MAXN], ans;
ll qpow(ll a, ll n) {ll ret = 1; for(; n; n >>= 1, a = a * a % P) if(n & 1) ret = ret * a % P; return ret;}
int main() {
	n = read(); K = read();
	s[0] = '@';
	for(int i = 1; i <= n; i++) s[i] = readc();
	for(int c = 0, i = 1; i <= n; i++) {
		if(i < c + r[c]) r[i] = min(c + r[c] - i, r[2 * c - i]);
		while(i + r[i] <= n && s[i + r[i]] == s[i - r[i]]) r[i]++;
		if(i + r[i] > c + r[c]) c = i;
	}
	for(int i = 1; i <= n; i++) t[1]++, t[r[i]+1]--;
	for(int i = 1; i <= n; i++) t[i] += t[i-1];
	ans = 1;
	for(int i = n; i >= 1; i--) {
		ll d = min(t[i], K);
		ans = (ans * qpow(2 * i - 1, d)) % P;
		K -= d;
	}
	if(K) printf("-1\n");
	else printf("%lld\n", ans);
	return 0;
}
