#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ldb;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 55;
const ldb eps = 1e-12;
int n;
ldb a[MAXN][MAXN];
ldb Abs(ldb x) {
	return x < 0 ? -x : x;
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n+1; j++)
			a[i][j] = read();
	int r = 1;
	for(int c = 1; c <= n; c++) {
		int num = r;
		for(int i = r+1; i <= n; i++)
			if(Abs(a[i][c]) > Abs(a[num][c])) num = i;
		if(Abs(a[num][c]) < eps) continue;
		for(int i = c; i <= n+1; i++) swap(a[r][i], a[num][i]);
		for(int i = r+1; i <= n; i++) {
			ldb tmp = a[i][c] / a[r][c];
			for(int j = c; j <= n+1; j++)
				a[i][j] -= a[r][j] * tmp;
		}
		r++;
	}
	if(r <= n) {
		for(int i = r; i <= n; i++)
			if(Abs(a[i][n+1]) > 0) {
				printf("-1\n");
				return 0;
			}
		printf("0\n");
		return 0;
	}
	for(int i = n; i >= 1; i--) {
		for(int j = i+1; j <= n; j++) a[i][n+1] -= a[j][n+1] * a[i][j];
		a[i][n+1] /= a[i][i];
	}
	for(int i = 1; i <= n; i++) {
		printf("x%d=", i);
		if(Abs(a[i][n+1]) < eps) printf("0.00\n");
		else printf("%.2Lf\n", a[i][n+1]);
	}
	return 0;
}
