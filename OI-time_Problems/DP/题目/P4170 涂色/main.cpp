// https://www.luogu.com.cn/problem/P4170
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
const int MAXN = 55;
const int INF = 0x3f3f3f3f;
char s[MAXN];
int n, f[MAXN][MAXN];
int main() {
    scanf("%s", s+1);
    n = strlen(s+1);
    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= n; i++) f[i][i] = 1;
    for(int len = 2; len <= n; len++)
        for(int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if(s[l] == s[r]) f[l][r] = min(f[l+1][r], f[l][r-1]);
            else {
                for(int k = l; k < r; k++) 
                f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
            }
        }
    printf("%d\n", f[1][n]);

    return 0;
}