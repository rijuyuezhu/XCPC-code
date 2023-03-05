#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e5 + 5;
db Srt[MAXN], p[MAXN];
int n, a[MAXN];
db Y(int i, int j) {return a[j] + Srt[i-j];}
void solve(int l, int r, int L, int R) {
	if(l > r) return;
	int m = (l + r) >> 1, j0 = 0; db mx = 0;
	for(int j = L; j <= m && j <= R; j++)
		if(Y(m, j) > mx) mx = Y(m, j), j0 = j;
	p[m] = max(p[m], mx);
	solve(l, m-1, L, j0); solve(m+1, r, j0, R);
}
int main() {
	n = read(); for(int i = 1; i <= n; i++) a[i] = read(), Srt[i] = sqrt(i);
	solve(1, n, 1, n);
	reverse(a + 1, a + 1 + n); reverse(p + 1, p + 1 + n);
	solve(1, n, 1, n);
	for(int i = n; i >= 1; i--) printf("%d\n", (int)ceil(p[i]) - a[i]);
	return 0;
}
