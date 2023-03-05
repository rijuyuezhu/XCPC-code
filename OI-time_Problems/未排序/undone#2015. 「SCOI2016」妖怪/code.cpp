#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e6 + 5;
int n;
db p[MAXN], q[MAXN];
db f(db x) {
	db ret = 0.0;
	for(int i = 1; i <= n; i++)
		ret = max(ret, p[i] + q[i] + p[i] * x + q[i] / x);
	return ret;
}
int main() {
	n = read();
	db l = 1e20, r = 0.0;
	for(int i = 1; i <= n; i++) {
		p[i] = read(), q[i] = read();
		db x = sqrt(q[i] / p[i]);
		l = min(l, x - 1e-5); r = max(r, x + 1e-5);
	}
	if(l < 1e-5) l = 1e-5;
	while(r - l > 1e-5) {
		db lm = l + (r - l) / 2, rm = r - (r - l) / 2;
		if(f(lm) > f(rm)) l = lm;
		else r = rm;
	}
	printf("%.4lf\n", f(l));
	return 0;
}
