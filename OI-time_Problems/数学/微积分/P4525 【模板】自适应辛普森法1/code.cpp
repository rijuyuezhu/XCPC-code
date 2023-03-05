#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef double db;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
db a, b, c, d, l, r;
db f(db x) {return (c * x + d) / (a * x + b);}
db simpson(db l, db r) {
	db m = (l + r) / 2;
	return (f(l) + f(r) + 4 * f(m)) * (r-l) / 6;
}
db asr(db l, db r, db eps, db ans) {
	db m = (l + r) / 2;
	db L = simpson(l, m), R = simpson(m, r);
	if(fabs(L + R - ans) <= 15*eps) return L + R + (L+R-ans)/15;
	return asr(l, m, eps/2, L) + asr(m, r, eps/2, R);
}
int main() {
	scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
	printf("%.6lf\n", asr(l, r, 1e-6, simpson(l, r)));
	return 0;
}
