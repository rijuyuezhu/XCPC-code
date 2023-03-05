// https://www.luogu.com.cn/problem/P2657
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
int dp[11][10];//dp[i][j] : i位，头上是j
int a[11], len;
int solve(int x) {
    len = 0;
    int ans = 0;
    while(x) {
        a[++len] = x % 10;
        x /= 10;
    }
    for(int i = 1; i < len; i++)
        for(int j = 1; j <= 9; j++) //不含前导0
            ans += dp[i][j];
    for(int i = 1; i < a[len]; i++) ans += dp[len][i];
    
    for(int i = len - 1; i >= 1; i--) {
        for(int j = 0; j < a[i]; j++)//[i+1,len]都与x相同，枚举第i位
            if(abs(j - a[i+1]) >= 2) ans += dp[i][j];
        if(abs(a[i] - a[i+1]) < 2) break;
    }
    return ans;
}
int main() {
    for(int i = 0; i <= 9; i++) dp[1][i] = 1;
    for(int i = 2; i <= 10; i++)
        for(int j = 0; j <= 9; j++) // i
            for(int k = 0; k <= 9; k++) //i - 1
                if(abs(j - k) >= 2)
                    dp[i][j] += dp[i - 1][k];
    int a = read(), b = read();
    printf("%d\n", solve(b + 1) - solve(a));
    return 0;
}