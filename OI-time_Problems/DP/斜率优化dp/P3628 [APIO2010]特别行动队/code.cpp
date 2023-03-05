#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e6 + 5;
ll a, b, c, x[MAXN], S[MAXN], f[MAXN], q[MAXN], hd, tl;
int n;
ll sqr(ll x) {return x * x;}
ll calc(int j, int i) {
	return f[j] + a * sqr(S[i] - S[j]) + b * (S[i] - S[j]) + c;
}
ll Val(int i) {return f[i] + a * sqr(S[i]) - b * S[i];}
db slope(int i, int j) {
	return db(Val(i) - Val(j)) / (S[i] - S[j]);
}
int main() {
	n = read();
	a = read(), b = read(), c = read();
	for(int i = 1; i <= n; i++) x[i] = read();
	for(int i = 1; i <= n; i++) S[i] = S[i-1] + x[i];
	q[hd = tl = 1] = 0;
	for(int i = 1; i <= n; i++) {
		while(hd < tl && slope(q[hd], q[hd+1]) >= 2 * a * S[i]) hd++;
		f[i] = calc(q[hd], i);
		while(hd < tl && slope(q[tl-1], q[tl]) <= slope(q[tl], i)) tl--;
		q[++tl] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
