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
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
const int P = 1e9 + 7;
const int B = 17;
int pls(int a, int b) {a += b; return a >= P ? a - P : a;}
int mns(int a, int b) {a -= b; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, m, f[MAXN][B], upto[MAXN][B];
int getup(int u, int k) {return upto[u][k] == u ? u : upto[u][k] = getup(upto[u][k], k);}
void merge(int u, int v, int k) {
	if(getup(u, k) != getup(v, k))
		upto[getup(u, k)][k] = getup(v, k);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int k = 0; k < B; k++)
			upto[i][k] = i;
	for(int i = 1; i <= m; i++) {
		int l1 = read(), r1 = read(), l2 = read(), r2 = read();
		for(int k = B-1; k >= 0; k--)
			if(l1 + (1 << k) - 1 <= r1) {
				merge(l1, l2, k);
				l1 += (1 << k);
				l2 += (1 << k);
		}
	}
	for(int k = B-1; k > 0; k--) 
		for(int i = 1; i <= n; i++) {
			int j = getup(i, k);
			merge(i, j, k-1), merge(i + (1 << (k-1)), j + (1 << (k-1)), k-1);
		}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(getup(i, 0) == i) cnt++;
	printf("%d\n", mul(9, qpow(10, cnt-1)));
	return 0;
}
