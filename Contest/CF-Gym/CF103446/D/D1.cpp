#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
using db = double;
constexpr db eps = 1e-6;
db p, q;

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

pair<int, int> work() {
    cin >> p >> q;
    int g1 = gcd(round(p), round(q));
    p /= g1; q /= g1;
    if(p - 2 * q < 2 * eps)
        return {0, 0};
    db m = (p + sqrt(p * p - 4 * q * q)) / 2;
    if(fabs(m - round(m)) > eps)
        return {0, 0};
    int a = round(q), b = round(m), g = gcd(a, b);
    return {a / g, b / g};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--) {
        pair<int, int> ans = work();
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}
