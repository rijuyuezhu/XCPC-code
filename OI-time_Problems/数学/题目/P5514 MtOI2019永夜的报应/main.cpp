//https://www.luogu.com.cn/problem/P5514
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
int n;
int ans = 0;
int main() {
    int n = read();
    for(int i = 1; i <= n; i++) ans ^= read();
    printf("%lld\n", ans);
    return 0;
}