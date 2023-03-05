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
int f[15][15][2][2];
int dfs(int len, int lst, int lim, int zero) {
    if(!len) return 1;
    if(~f[len][lst][lim][zero]) return f[len][lst][lim][zero];
    int res = 0;
    for(int i = 0; i <= 9; i++)
        if((!lim || i <= num[len]) && (zero || abs(i - lst) >= 2))
            res += dfs(len - 1, i, lim && (i == num[len]), zero && (i == 0));
    f[len][lst][lim][zero] = res;
    return res;

}
int calc(int x) {
    memset(num, 0, sizeof num); cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    memset(f, -1, sizeof f);
    return dfs(cnt, 0, 1, 1);
}
int main() {
    int a = read(), b = read();
    printf("%d\n", calc(b) - calc(a-1));    
    return 0;
}