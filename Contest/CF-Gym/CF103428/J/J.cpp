#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a % b);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--) {
        ll a, b;
        cin >> a >> b;
        ll g = gcd(a, 180 * b);
        cout << (180 * b / g - 1) << '\n';
    }
    return 0;
}
