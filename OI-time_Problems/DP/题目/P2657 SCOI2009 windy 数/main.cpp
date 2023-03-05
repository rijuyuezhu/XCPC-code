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

int num[15], cnt;
int f[15][15];
int dfs(int len, int lst, int lim, int zero) {
    if(!len) return 1;
    if(!lim && !zero && ~f[len][lst]) return f[len][lst];
    int up = lim ? num[len] : 9, ans = 0;
    for(int i = 0; i <= up; i++)
        if(zero || (abs(i - lst) >= 2)) 
            ans += dfs(len - 1, i, lim && (i == up), zero && (i == 0));
    if(!lim && !zero) f[len][lst] = ans;
    return ans;
}
int calc(int x) {
    memset(num, 0x00, sizeof num); cnt = 0;
    memset(f, -1, sizeof f);
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, -1, 1, 1);
}
int main() {
    int a = read(), b = read();
    printf("%d\n", calc(b) - calc(a-1));
    return 0;
}