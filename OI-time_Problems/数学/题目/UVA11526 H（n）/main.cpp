// https://www.luogu.com.cn/problem/UVA11526
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
int T, n;
ll ans;
int main() {
    T = read();
    while(T--) {
        n = read();
        ans = 0;
        for(int i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            ans += (j - i + 1) * (n / i);
        } 
        printf("%lld\n", ans);
    }
    return 0;
}
