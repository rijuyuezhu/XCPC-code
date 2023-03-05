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
const int MAXN = 505, P = 1e9 + 7;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, p, m, A[MAXN][MAXN], B[MAXN][MAXN], ret[MAXN][MAXN];
int main() {
	n = read(), p = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= p; j++)
			A[i][j] = (read() % P + P) % P;
	for(int i = 1; i <= p; i++)
		for(int j = 1; j <= m; j++)
			B[i][j] = (read() % P + P) % P;
	for(int i = 1; i <= n; i++)
		for(int k = 1; k <= p; k++)
			for(int j = 1; j <= m; j++)
				ret[i][j] = pls(ret[i][j], mul(A[i][k], B[k][j]));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) 
			printf("%d ", ret[i][j]);
		printf("\n");
	}
	return 0;
}
