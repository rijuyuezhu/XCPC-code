// https://www.acwing.com/problem/content/243/
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
const int MAXN = 200005;
int n;
ll t[MAXN], a[MAXN], l[MAXN], r[MAXN], ans;
int lowbit(int x) {return x & (-x);}
ll sum(int x) {
    ll ans = 0;
    for(int i = x; i; i -= lowbit(i)) ans += t[i];
    return ans;
}
void add(int x, ll k) {
    for(int i = x; i <= n; i += lowbit(i)) t[i] += k;
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read();

    memset(t, 0x00, sizeof t);
    for(int i = 1; i <= n; i++) {
        l[i] = sum(n) - sum(a[i]);
        add(a[i], 1);
    }
    memset(t, 0x00, sizeof t);
    for(int i = n; i >= 1; i--) {
        r[i] = sum(n) - sum(a[i]);
        add(a[i], 1);
    }
    ans = 0;
    for(int i = 1; i <= n; i++) ans += l[i] * r[i];
    printf("%lld ", ans);

    memset(t, 0x00, sizeof t);
    for(int i = 1; i <= n; i++) {
        l[i] = sum(a[i] - 1);
        add(a[i], 1);
    }
    memset(t, 0x00, sizeof t);
    for(int i = n; i >= 1; i--) {
        r[i] = sum(a[i] - 1);
        add(a[i], 1);
    }
    ans = 0;
    for(int i = 1; i <= n; i++) ans += l[i] * r[i];
    printf("%lld ", ans);
    return 0;
}