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
const int MAXN = 505;
const ldb eps = 1e-5;
int n, m, c[MAXN], seq[MAXN], anscost, anscnt;
bool cmp(int a, int b) {return c[a] < c[b];}
ldb Abs(ldb a) {return a > 0 ? a : -a;}
bool eq(ldb a, ldb b) {return Abs(a - b) < eps;}
struct Vec {
	ldb a[MAXN];
	ldb& operator [](const int& k) {return a[k];}
	ldb operator [](const int& k)const {return a[k];}
}z[MAXN];
namespace Linearbasis {
	Vec t[MAXN];
	bool pl[MAXN];
	bool ins(Vec A) {
		for(int i = 1; i <= m; i++)
			if(!eq(A[i], 0)) {
				if(!pl[i]) {
					t[i] = A;
					pl[i] = 1;
					return 1;
				} else {
					ldb k = A[i] / t[i][i];
					for(int j = i; j <= m; j++) A[j] -= t[i][j] * k;
				}
			}
		return 0;
	}
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			z[i][j] = read();
	for(int i = 1; i <= n; i++) c[i] = read(), seq[i] = i;
	sort(seq + 1, seq + 1 + n, cmp);
	for(int i = 1; i <= n; i++) {
		int now = seq[i];
		if(Linearbasis::ins(z[now])) {
			anscnt++; anscost += c[now];
		}
	}
	printf("%d %d\n", anscnt, anscost);
	return 0;
}
