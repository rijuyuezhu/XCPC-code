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
const int MAXN = 1e6 + 5;
ll n, a[MAXN], sum[MAXN], k;
ll b[MAXN];

int main() {
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read(), sum[i] = sum[i-1] + a[i];
    k = read();
    for(int l = 1, r = 1; l <= n && sum[l] <= k; l++) {
        while(r < n && sum[r+1] - sum[l] < sum[l]) r++;
        if(r == n) {
            b[sum[l]]++;
            break;
        }
        ll mn = sum[l], mx = sum[r+1] - sum[l];//[mn, mx)
        b[sum[l]]++;
        if(mx <= k) b[mx]--;
    }
    int ans = 0;
    for(int i = 1; i <= k; i++) {
        b[i] += b[i-1];
        if(b[i]) ans++;
    }
    printf("%d\n", ans);
    for(int i = 1; i <= k; i++) 
        if(b[i]) printf("%d ", i);
    printf("\n");
    return 0;
}
