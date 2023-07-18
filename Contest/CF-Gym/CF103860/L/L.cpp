#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAXM = 2e5 + 5;
int m;
ll x, y, n, p[MAXM], ans;
ll floordiv(ll a, ll b) {
    ll ret = a / b;
    if(ret * b > a) --ret;
    return ret;
}
ll calc(ll pre2, ll pre1, ll ed) {
    if(pre1 + x + 1 >= pre2 + y + 2) {
        //cerr << "tr 1" << endl;
        ll t1 = floordiv(2 * (ed - 1 - pre1), y + 2) - 1;
        if(abs(t1 % 2) == 0) --t1;
        ll t2 = floordiv(2 * (ed - 1 - pre2), y + 2) - 2;
        if(abs(t2 % 2) == 1) --t2;
        //cerr << "here " << t1 << ' ' << t2 << endl;
        if(t1 < 0 && t2 < 0)
            return pre1;
        ans += max(t1, t2) + 1;
        if(t1 > t2)
            return pre1 + (t1 + 1) / 2 * (y + 2);
        else
            return pre2 + (t2 / 2 + 1) * (y + 2);
    } else {
        //cerr << "tr 2" << endl;
        ll t1 = floordiv(2 * (ed - 1 - pre1), y + 2) - 1;
        if(abs(t1 % 2) == 0) --t1;
        ll t2 = floordiv(2 * (ed - 1 - pre1 - x - 1), y + 2);
        if(abs(t2 % 2) == 1) --t2;
        //cerr << "here " << t1 << ' ' << t2 << endl;
        if(t1 < 0 && t2 < 0)
            return pre1;
        ans += max(t1, t2) + 1;
        if(t1 > t2)
            return pre1 + (t1 + 1) / 2 * (y + 2);
        else
            return pre1 + x - 1 + t2 / 2 * (y + 2);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin >> n >> m >> x >> y;
    for(int i = 1; i <= m; i++)
        cin >> p[i];
    ans = 0;
    p[0] = 0; p[m+1] = n+1;
    ll pre2 = 0;
    for(int i = 0; i <= m; i++) {
        //cerr << pre2 << ' ' << p[i] << ' ' << p[i+1] << endl;
        //ll lans = ans;
        pre2 = calc(pre2, p[i], p[i+1]);
        //cerr << "now ans: " << ans - lans << endl;
    }
    cout << ans << '\n';
    return 0;
}

