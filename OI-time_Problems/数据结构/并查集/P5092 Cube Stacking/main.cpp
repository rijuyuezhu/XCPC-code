// https://www.luogu.com.cn/problem/P5092
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
int getup(int x) {
    if(x == upto[x]) return x;
    int f = getup(upto[x]);
    dist[x] += dist[upto[x]];
    return upto[x] = f;
}
int main() {
    for(int i = 1; i < MAXN; i++) upto[i] = i, dist[i] = 0, sz[i] = 1;
    int P = read();
    while(P--) {
        char s[5];
        scanf("%s", s);
        if(s[0] == 'M') {
            int x = read(), y = read();
            int fx = getup(x), fy = getup(y);
            upto[fx] = fy; dist[fx] = sz[fy];
            sz[fy] += sz[fx];
        } else {
            int x = read();
            getup(x);
            printf("%d\n", dist[x]);
        }
    }
    return 0;
}