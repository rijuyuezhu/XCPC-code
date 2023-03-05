// https://www.luogu.com.cn/problem/P2569
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
const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll T, P, W;
ll AP[MAXN], BP[MAXN], AS[MAXN], BS[MAXN];
ll dp[MAXN][MAXN];
int que[MAXN], hd, tl;
ll calc1(int i, int t) {
    return dp[i - W - 1][t] + t * AP[i];
}
ll calc2(int i, int t) {
    return dp[i - W - 1][t] + t * BP[i];
}
int main() {
    T = read(); P = read(); W = read();
    if(T == 0) {
        printf("0\n");
        return 0;
    }
    for(int i = 1; i <= T; i++) 
        AP[i] = read(), BP[i] = read(), AS[i] = read(), BS[i] = read();
    for(int i = 1; i <= T; i++) {
        for(int j = 0; j <= AS[i]; j++)
            dp[i][j] = -j * AP[i];
        for(int j = AS[i] + 1; j <= P; j++)
            dp[i][j] = -INF;
    }//1
    for(int i = 2; i <= T; i++) {
        for(int j = 0; j <= P; j++) dp[i][j] = max(dp[i][j], dp[i-1][j]);//2
        if(i >= W + 2) {
            //one
            hd = 1; tl = 0;
            for(int j = 0; j <= P; j++) {
                while(hd <= tl && que[hd] < j - AS[i]) hd++;
                if(j-1 >= 0) {
                    while(hd <= tl && calc1(i, que[tl]) <= calc1(i, j-1)) tl--;
                    que[++tl] = j-1;
                }
                if(hd <= tl) dp[i][j] = max(dp[i][j], calc1(i, que[hd]) - j * AP[i]);
            }
            //two
            hd = 1; tl = 0;
            for(int k = 1; k <= BS[i]; k++) {
                while(hd <= tl && calc2(i, que[tl]) <= calc2(i, k)) tl--;
                que[++tl] = k;
            }
            for(int j = 0; j <= P; j++) {
                while(hd <= tl && que[hd] <= j) hd++;
                if(j+BS[i] <= P) {
                    while(hd <= tl && calc2(i, que[tl]) <= calc2(i, j+BS[i])) tl--;
                    que[++tl] = j+BS[i];
                }
                if(hd <= tl) dp[i][j] = max(dp[i][j], calc2(i, que[hd]) - j * BP[i]);
            }
        }
    }
    ll ans = -INF;
    for(int i = 0; i <= P; i++) ans = max(ans, dp[T][i]);
    printf("%lld\n", ans);
    return 0;
}