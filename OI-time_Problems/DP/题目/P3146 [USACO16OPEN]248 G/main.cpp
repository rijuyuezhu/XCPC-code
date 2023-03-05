//https://www.luogu.com.cn/problem/P3146
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 250;
int f[MAXN][MAXN];
int n;
int ans;
int main() {
    n = read();
    for(int i = 1; i <= n; i++) f[i][i] = read(), ans = max(ans, f[i][i]);
    for(int l = 2; l <= n; l++)
        for(int i = 1; i + l - 1 <= n; i++) {
            int j = i + l - 1;
            for(int k = i; k < j; k++) 
                if(f[i][k] != 0 && f[k+1][j] != 0 && f[i][k] == f[k+1][j]) {
                    f[i][j] = max(f[i][j], f[i][k] + 1);
                    ans = max(f[i][j], ans);
                }
        }
    printf("%d\n", ans);
    return 0;
}