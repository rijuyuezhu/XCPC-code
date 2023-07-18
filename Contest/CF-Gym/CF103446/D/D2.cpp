#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

ll p, q;
vector<pair<ll, ll> > division;

ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a % b);
}

void divide(ll n) {
    division.clear();
    for(ll i = 2; i * i <= n; i++)
        if(n % i == 0) {
            pair<ll, ll> ret = {i, 1};
            while(n % i == 0) {
                ret.second *= i;
                n /= i;
            }
            division.push_back(ret);
        }
    if(n > 1)
        division.push_back({n, n});
}

void work() {
    cin >> p >> q;
    ll g = gcd(p, q);
    p /= g; q /= g;
    divide(q);
    int n = division.size(), U = 1 << n;
    for(int k = 0; k < U; k++) {
        ll a = 1, b;
        for(int i = 0; i < n; i++)
            if((k >> i) & 1)
                a *= division[i].second;
        b = q / a;
        if(a * a + b * b == p) {
            cout << a << ' ' << b << '\n';
            return ;
        }
    }
    cout << 0 << ' ' << 0 << '\n';
    return ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--)
        work();
    return 0;
}
