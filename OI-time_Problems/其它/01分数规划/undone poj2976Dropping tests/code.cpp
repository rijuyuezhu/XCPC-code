#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 1005;
const db eps = 1e-4;
int n, k;
db a[MAXN], b[MAXN], v[MAXN];
bool check(db t) {
	for(int i = 1; i <= n; i++) v[i] = a[i] - t * b[i];
	sort(v + 1, v + 1 + n);
	db ret = 0;
	for(int i = k+1; i <= n; i++) ret += v[i];
	return ret >= 0;
}
int main() {
	while(1) {
		n = read(); k = read();
		if(!n && !k) break;
		for(int i = 1; i <= n; i++) a[i] = read();
		for(int i = 1; i <= n; i++) b[i] = read();
		db l = 0, r = 1;
		while(r - l > eps) {
			db m = (l + r) / 2;
			if(check(m)) l = m;
			else r = m;
		}
		printf("%.0lf\n", 100.0 * l);
	}
	return 0;
}
