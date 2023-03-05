//http://poj.org/problem?id=2411
#include<cstdio>
#include<cstring>

using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 11;
ll f[MAXN + 1][1 << MAXN];
bool legal[1 << MAXN];//判断i有没有连续偶数个零（预处理）
int h, w;
int U;
int main() {
    while(1) {
        h = read(), w = read();
        if(h == 0) return 0;
        U = (1 << w) - 1;

        for(int i = 0; i <= U; i++) {
            int cnt0 = 0;
            legal[i] = 1;
            for(int j = 0; j < w; j++) {
                int now = (i >> j) & 1;
                if(now == 0) cnt0 ^= 1;
                else {
                    if(cnt0) {
                        legal[i] = 0;
                        break;
                    }
                    cnt0 = 0;
                }
            }
            if(cnt0) legal[i] = 0;
        }

        f[0][0] = 1;
        for(int i = 1; i <= h; i++)
            for(int j = 0; j <= U; j++) {//i
                f[i][j] = 0;
                for(int k = 0; k <= U; k++) //i - 1
                    if((j & k) == 0 && legal[j | k])
                        f[i][j] += f[i - 1][k];
            }
        printf("%lld\n", f[h][0]);
    }
    return 0;
}