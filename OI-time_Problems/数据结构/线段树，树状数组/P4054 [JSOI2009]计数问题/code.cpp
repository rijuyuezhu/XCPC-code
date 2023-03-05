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
const int MAXN = 305;
const int MAXV = 105;
int n, m, val[MAXN][MAXN];
struct BIT {
	int t[MAXN][MAXN];
	int lowbit(int x) {return x&-x;}
	void add(int x, int y, int v) {
		for(int i = x; i <= n; i += lowbit(i))
			for(int j = y; j <= m; j += lowbit(j))
				t[i][j] += v;
	}
	int sum(int x, int y) {
		int ret = 0;
		for(int i = x; i; i -= lowbit(i))
			for(int j = y; j; j -= lowbit(j))
				ret += t[i][j];
		return ret;
	}
	int sum(int x1, int x2, int y1, int y2) {
		return sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
	}
}bit[MAXV];

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			val[i][j] = read();
			bit[val[i][j]].add(i, j, 1);
		}
	int q = read();
	while(q--) {
		int opt = read();
		if(opt == 1) {
			int x = read(), y = read(), c = read();
			bit[val[x][y]].add(x, y, -1);
			bit[val[x][y] = c].add(x, y, 1);
		} else {
			int x1 = read(), x2 = read(), y1 = read(), y2 = read(), c = read();
			printf("%d\n", bit[c].sum(x1, x2, y1, y2));
		}
	}
	return 0;
}
