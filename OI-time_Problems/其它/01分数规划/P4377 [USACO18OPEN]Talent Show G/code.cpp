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
const int MAXN = 255, MAXW = 1005;
const db inf = 1e20, eps = 1e-4;
int n, W, w[MAXN], t[MAXN];
db f[MAXN][MAXW];
void chkmax(db& a, db b) {a = max(a, b);}
bool check(db m) {
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= W; j++)
			f[i][j] = -inf;
	f[0][0] = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j <= W; j++) {
			int nw = w[i+1]; db v = t[i+1] - m * w[i+1];
			chkmax(f[i+1][min(j+nw, W)], f[i][j] + v);
			chkmax(f[i+1][j], f[i][j]);
		}
	return f[n][W] >= 0.0;
}
int main() {
	n = read(); W = read();
	for(int i = 1; i <= n; i++) w[i] = read(), t[i] = read();
	db l = 0, r = 1e6;
	while(r - l > eps) {
		db m = (l + r) / 2;
		if(check(m)) l = m;
		else r = m;
	}
	printf("%d\n", int(1000 * l));
	return 0;
}
