#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        int a, b;
        cin >> a >> b;
        int g = gcd(a, b);
        cout << ( 1ll * (a - 1) * (b - 1) + (g - 1) ) / 2 << '\n';
    }
    return 0;
}