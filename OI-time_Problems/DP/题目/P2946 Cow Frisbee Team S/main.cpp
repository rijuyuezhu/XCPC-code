// https://www.luogu.com.cn/problem/P2946
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
const int MAXN = 2005;
const int MAXF = 1005;
const int P = 1e8;
int pls(int u, int v, int mod = P) {return u + v < mod ? u + v : u + v - mod;}
int mns(int u, int v, int mod = P) {return u < v ? u - v + mod : u - v;}
int mul(int u, int v, int mod = P) {return 1ll * u * v % mod;}

int n, F;
int r[MAXN];
int f[MAXN][MAXF];
int main() {
    n = read(), F = read();
    for(int i = 1; i <= n; i++) r[i] = read() % F;
    memset(f, 0x00, sizeof f);
    f[0][0] = 1;
    for(int i = 1; i <= n; i++) 
        for(int j = 0; j < F; j++)
            f[i][j] = pls(f[i-1][j], f[i-1][mns(j, r[i], F)]);
    printf("%d\n", f[n][0] - 1);
    return 0;
}