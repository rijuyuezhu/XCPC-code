// https://www.luogu.com.cn/problem/P5656
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
ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}
void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= (a / b) * x;
}

int main() {
    int T = read();
    while(T--) {
        ll a = read(), b = read(), c = read(), x, y, g, xmin, ymin, xmax, ymax;
        g = gcd(a, b);
        if(c % g != 0) {
            printf("-1\n");
            continue;
        }
        a /= g, b /= g, c /= g;
        exgcd(a, b, x, y);
        x *= c; y *= c;
        xmin = (x % b + b) % b; if(xmin == 0) xmin += b;
        ymax = (c - a * xmin) / b;
        ymin = (y % a + a) % a; if(ymin == 0) ymin += a;
        xmax = (c - b * ymin) / a;
        if(ymax > 0) // has a int solution
        {
            printf("%lld %lld %lld %lld %lld\n", (ymax - ymin) / a + 1, xmin, ymin, xmax, ymax);
        } else {
            printf("%lld %lld\n", xmin, ymin);
        }
    }   
    return 0;
}