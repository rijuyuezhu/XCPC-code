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
const int MAXN = 405;
const int P = 1e9 + 7;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n = P-2) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, a[MAXN][2 * MAXN];

int main() {
	n = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			a[i][j] = read(); a[i][j + n] = (i == j);
		}
	for(int i = 1; i <= n; i++) {
		int num = -1;
		for(int j = i; j <= n; j++) if(a[j][i]) {num = j; break;}
		if(num == -1) {
			printf("No Solution\n");
			return 0;
		}
		if(num != i) for(int j = i; j <= 2 * n; j++) swap(a[num][j], a[i][j]);
		int in = qpow(a[i][i]);
		for(int j = 1; j <= n; j++) if(j != i) {
			int t = mul(a[j][i], in);
			for(int k = i; k <= 2 * n; k++)
				a[j][k] = mns(a[j][k], mul(a[i][k], t));
		}
		for(int j = i; j <= 2 * n; j++) a[i][j] = mul(a[i][j], in);
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) printf("%d ", a[i][j + n]);
		printf("\n");
	}
	return 0;
}
