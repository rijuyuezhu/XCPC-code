/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 14:26:58
 * @Description: http://acm.hdu.edu.cn/contest/problems?cid=1047
 * or http://acm.hdu.edu.cn/showproblem.php?pid=7174
 * @Tag: 区间DP，DP，括号序列 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 505;

const int P = 1e9 + 7;
struct mint {
	int v;
	mint(int v=0) : v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}

int n, m, a[MAXN];
mint f[MAXN][MAXN], g[MAXN][MAXN];
mint kinds(int x, int y) {
	if(x == 0 && y == 0) return m;
	else if(x > 0 && y == 0) return 1;
	else if(x == 0 && y < 0) return 1;
	else if(x > 0 && y < 0 && x + y == 0) return 1;
	else return 0;
}
void work() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	if(n & 1) {
		printf("0\n");
		return ;
	}
	for(int i = 0; i <= n+1; i++)
		for(int j = 0; j <= n+1; j++)
			f[i][j] = g[i][j] = 0;
	for(int i = 1; i <= n+1; i++) g[i][i-1] = 1;
	for(int l = 2; l <= n; l += 2)
		for(int i = 1; i + l - 1 <= n; i++) {
			int j = i + l - 1;
			f[i][j] = kinds(a[i], a[j]) * g[i+1][j-1];
			for(int k = i; k <= j; k += 2)
				g[i][j] = g[i][j] + g[i][k-1] * f[k][j];
		}
	printf("%d\n", g[1][n].v);
}
int main() {
	int t = read();
	while(t--) work();
	return 0;
}