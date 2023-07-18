#include <iostream>
#include <algorithm>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
int w, d, h, a, b, f, g;
int Dist(int a, int b, int x, int y) {
    return abs(a - x) + abs(b - y);
}
void work() {
    cin >> w >> d >> h >> a >> b >> f >> g;
    int ans = INF;
    ans = min(ans, Dist(a, b, f, -h-g));
    ans = min(ans, Dist(a, b, -h-f, g));
    ans = min(ans, Dist(a, b, f, d+h+d-g));
    ans = min(ans, Dist(a, b, w+h+w-f, g));
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
