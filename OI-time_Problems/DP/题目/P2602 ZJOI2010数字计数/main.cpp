// https://www.luogu.com.cn/problem/P2602
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
    return f * x;
}

typedef unsigned long long ull;
ull a, b;
int num[15], cnt;
ull f[15][15]; 
int vis[15][15];
ull dfs(int len, int sum, int lim, int zero, int t) {
    if(!len) return sum;
    if(!lim && !zero && vis[len][sum]) return f[len][sum];
    int up = lim ? num[len] : 9; ull ans = 0;
    for(int i = 0; i <= up; i++) 
        ans += dfs(len-1, sum + ((i == t) && (i || !zero)), lim && (i == up), !i && zero, t);
    if(!lim && !zero) {
        vis[len][sum] = 1; f[len][sum] = ans;
    }
    return ans;
}
ull calc(ull x, int t) {
    memset(num, 0x00, sizeof num); cnt = 0;
    memset(f, 0x00, sizeof f); memset(vis, 0x00, sizeof vis);
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, 0, 1, 1, t);    
}
int main() {
    scanf("%llu%llu", &a, &b);
    for(int i = 0; i <= 9; i++)
        printf("%llu%c", calc(b, i) - calc(a-1, i), i == 9 ? '\n' : ' ');
    return 0;
}