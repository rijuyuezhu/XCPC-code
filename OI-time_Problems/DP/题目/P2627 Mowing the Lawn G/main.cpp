// https://www.luogu.com.cn/problem/P2627
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
const int MAXN = 100005;
int n, k;
ll E[MAXN], sum[MAXN], dp[MAXN];
int que[MAXN], hd, tl;
ll calc(int i) {
    if(i >= 1) return dp[i-1] - sum[i];
    return -sum[i];
}
int main() {
    n = read(); k = read();
    for(int i = 1; i <= n; i++) E[i] = read(), sum[i] = sum[i-1] + E[i];
    dp[0] = 0;
    hd = 1; tl = 0;
    que[++tl] = 0;
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        while(hd <= tl && que[hd] < i-k) hd++;
        if(hd <= tl) dp[i] = max(dp[i], calc(que[hd]) + sum[i]);
        while(hd <= tl && calc(que[tl]) <= calc(i)) tl--;
        que[++tl] = i;
    }
    printf("%lld\n", dp[n]);
    //for(int i = 1; i <= n; i++) printf("%lld ", dp[i]);
    return 0;
}