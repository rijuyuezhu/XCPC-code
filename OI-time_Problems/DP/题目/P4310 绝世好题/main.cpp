//https://www.luogu.com.cn/problem/P4310
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
int n;
int f[35];

int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        int maxlen = 0;
        int now = read();
        for(int j = 0; j <= 30; j++) 
            if(now & (1 << j)) maxlen = max(maxlen, f[j] + 1);
        for(int j = 0; j <= 30; j++)
            if(now & (1 << j)) f[j] = max(f[j], maxlen);
    }
    int ans = 0;
    for(int i = 0; i <= 30; i++) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}