// https://www.luogu.com.cn/problem/P4302
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
const int MAXL = 105;
char s[MAXL];
int n;
int num[MAXL];
int f[MAXL][MAXL];
bool check(int t, int l, int len) {
    for(int i = 0; i < len; i++)
        if(s[l + i] != s[l + i % t]) return false;
    return true;
}
int main() {
    scanf("%s", s+1); n = strlen(s+1);
    for(int i = 0; i <= 9; i++) num[i] = 1;
    for(int i = 10; i <= 99; i++) num[i] = 2;
    num[100] = 3;
    for(int len = 1; len <= n; len++)
        for(int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            f[l][r] = len;
            for(int k = l; k < r; k++) f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
            for(int t = 1; t < len; t++) //循环节
            {
                if(len % t != 0) continue;
                if(check(t, l, len)) f[l][r] = min(f[l][r], num[len / t] + 2 + f[l][l + t - 1]);
            }
        }
    printf("%d\n", f[1][n]);
    return 0;
}