// https://www.luogu.com.cn/problem/P3383
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
const int MAXN = 1e8 + 5;
int n, q;
bool isprime[MAXN];
int prime[6000005], tot;
int main() {
    n = read(), q = read();
    for(int i = 1; i <= n; i++) isprime[i] = 1;
    isprime[0] = isprime[1] = 0;
    for(int i = 2; i <= n; i++) {
        if(isprime[i]) prime[++tot] = i;
        for(int j = 1; j <= tot && 1ll * prime[j] * i <= n; j++) {
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0) break;
        }
    }
    for(int i = 1; i <= q; i++) {
        int k = read();
        printf("%d\n", prime[k]);
    }
    return 0;
}