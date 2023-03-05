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
const int MAXN = 105;
const ldb eps = 1e-12;
ldb a[MAXN][MAXN];
int n;
ldb Abs(ldb x) {return x < 0 ? -x : x;}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= n+1; j++)
			a[i][j] = read();
	for(int i = 1; i <= n; i++) {
		int num = i;
		for(int j = i+1; j <= n; j++)
			if(Abs(a[j][i]) > Abs(a[num][i])) num = j;
		for(int j = i; j <= n+1; j++) swap(a[i][j], a[num][j]);
		if(Abs(a[i][i]) < eps) {
			printf("No Solution\n");
			return 0;
		}
		for(int j = i+1; j <= n; j++) {
			ldb tmp = a[j][i] / a[i][i];
			for(int k = i; k <= n+1; k++)
				a[j][k] -= tmp * a[i][k];
		}
	}
	for(int i = n; i >= 1; i--) {
		for(int j = i+1; j <= n; j++) a[i][n+1] -= a[j][n+1] * a[i][j];
		a[i][n+1] /= a[i][i];
	}
	for(int i = 1; i <= n; i++)
		if(Abs(a[i][n+1]) < eps) printf("0.00\n");
		else printf("%.2Lf\n", a[i][n+1]);
	return 0;
}
