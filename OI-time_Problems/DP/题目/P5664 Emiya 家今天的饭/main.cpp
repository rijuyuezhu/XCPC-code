// https://www.luogu.com.cn/problem/P5664
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 105, MAXM = 2005;
const int P = 998244353;
int pls(int a, int b) {return a + b >= P ? a + b - P : a + b;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}

int n, m;
int a[MAXN][MAXM], s[MAXN];
int g[MAXN][MAXN], ans;
int f[MAXN][2 * MAXN], ans2;
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            a[i][j] = read(), s[i] = pls(s[i], a[i][j]);

    for(int i = 0; i <= n; i++) g[i][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            g[i][j] = pls(g[i-1][j], mul(s[i], g[i-1][j-1]));
    for(int j = 1; j <= n; j++) ans = pls(ans, g[n][j]);
    for(int col = 1; col <= m; col++) {
        memset(f, 0x00, sizeof f);  
        f[0][n] = 1;
        for(int i = 1; i <= n; i++)
            for(int j = n-i; j <= n+i; j++)
                f[i][j] = pls(f[i][j], pls(f[i-1][j], pls(mul(f[i-1][j-1], a[i][col]), mul(f[i-1][j+1], mns(s[i], a[i][col])))));
        for(int j = n+1; j <= 2 * n; j++)
            ans = mns(ans, f[n][j]);
    }
    printf("%d\n", ans);

    return 0;
}