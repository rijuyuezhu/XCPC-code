//https://www.luogu.com.cn/problem/P3842
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 20005;
int n;
int l[MAXN], r[MAXN];
int fl[MAXN], fr[MAXN];
int dist(int x1, int x2) {
    return abs(x1 - x2);
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) l[i] = read(), r[i] = read();
    l[0] = r[0] = 1;
    l[n+1] = r[n+1] = n;
    for(int i = 1; i <= n+1; i++) {
        fl[i] = min(fl[i-1] + dist(l[i-1], r[i-1]) + dist(r[i-1], l[i]),
                    fr[i-1] + dist(r[i-1], l[i-1]) + dist(l[i-1], l[i]));
        fr[i] = min(fl[i-1] + dist(l[i-1], r[i-1]) + dist(r[i-1], r[i]),
                    fr[i-1] + dist(r[i-1], l[i-1]) + dist(l[i-1], r[i]));
    }
    printf("%d\n", min(fl[n+1], fr[n+1]) + n-1);
    return 0;
}