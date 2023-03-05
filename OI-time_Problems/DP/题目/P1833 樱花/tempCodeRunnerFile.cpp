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
const int MAXN = 10005;
const int MAXT = 1005;
int n, T;
int f[MAXT];
int main() {
    int sh, sm, eh, em;
    scanf("%d:%d%d:%d%d", &sh, &sm, &eh, &em, &n);
    T = (eh * 60 + em) - (sh * 60 + sm);
    for(int i = 1; i <= n; i++) {
        int t = read(), c = read(), p = read();
        if(p == 0 || p * c > T) {
            for(int j = t; j <= T; j++)
                f[j] = max(f[j], f[j - t] + c);
        } else {
            for(int k = 1; k <= p; k <<= 1) {
                for(int j = T; j >= k * t; j--)
                    f[j] = max(f[j], f[j - k * t] + k * c);
                p -= k;
            }
            if(p)
                for(int j = T; j >= p * t; j--)
                    f[j] = max(f[j], f[j - p * t] + p * c);
        }
    }
    printf("%d\n", f[T]);
    return 0;
}