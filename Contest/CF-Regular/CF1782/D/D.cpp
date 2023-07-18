#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;
constexpr int MAXN = 55;
int n, a[MAXN], ans;

ll sqr(ll x) {
    return x * x;
}
bool issquare(ll x) {
    return sqr(ll(sqrt((double)x) + 0.5)) == x;
}
int gett(ll t) {
    int ret = 0;
    for(int i = 1; i <= n; i++)
        if(issquare(a[i] + t))
            ret++;
    //cerr << '(' << t << ' ' << ret << ')' << endl;
    return ret;
}
void check(int p, int q) {
    int val = a[q] - a[p];
    for(int i = 1; 1ll * i * i <= val; i++)
        if(val % i == 0) {
            int xny = i, xpy = val / i;
            if(xny % 2 != xpy % 2)
                continue;
            int x = (xpy - xny) / 2;
            ll t = 1ll * x * x - a[p];
            if(t < 0)
                continue;
            ans = max(ans, gett(t));
        }
}
void work() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    ans = 1;
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            check(i, j);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--)
        work();
    return 0;
}
