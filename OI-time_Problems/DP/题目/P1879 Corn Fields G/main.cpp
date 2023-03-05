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
const int MAXN = 12, MAXU = 1 << 12;
const int P = 100000000;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int m, n, U;
int mp[MAXN];
int f[MAXN][MAXU];
int main() {
    m = read(); n = read(); U = (1 << n) - 1;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            mp[i] = (mp[i] << 1) + (!read());
    for(int s = 0; s <= U; s++)
        if(!((s & mp[0]) || (s & (s << 1))))
            f[0][s] = 1;
    for(int i = 1; i < m; i++) 
        for(int s = 0; s <= U; s++)
            if(!((s & mp[i]) || (s & (s << 1)))) 
                for(int t = 0; t <= U; t++) 
                    if(!((t & mp[i-1]) || (t & (t << 1)) || (s & t)))
                        f[i][s] = pls(f[i][s], f[i-1][t]);
    int ans = 0;
    for(int s = 0; s <= U; s++)
        if(!((s & mp[m-1]) || (s & (s << 1))))
            ans = pls(ans, f[m - 1][s]);
    printf("%d\n", ans);
    return 0;
}