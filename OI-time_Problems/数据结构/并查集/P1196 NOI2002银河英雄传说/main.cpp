// https://www.luogu.com.cn/problem/P1196
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
const int MAXN = 30005;
int upto[MAXN], dist[MAXN], sz[MAXN];
int getup(int u) {
    if(upto[u] == u) return u;
    int f = getup(upto[u]);
    dist[u] += dist[upto[u]];
    return upto[u] = f;
}

int main() {
    int T = read();
    for(int i = 1; i <= 30000; i++) upto[i] = i, sz[i] = 1;
    while(T--) {
        char s[5];
        scanf("%s", s);
        if(s[0] == 'M') {
            int x = getup(read()), y = getup(read());
            upto[x] = y; dist[x] = sz[y];
            sz[y] += sz[x];
        } else {
            int x = read(), y = read();
            if(getup(x) != getup(y)) {
                printf("-1\n");
            } else {
                printf("%d\n", abs(dist[x] - dist[y]) - 1);
            }
        }
    }
    return 0;
}
