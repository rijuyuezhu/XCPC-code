#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;
int n;
ll D[MAXN];
ll ans;
bool cmp(ll a, ll b) {
    return a > b;
}
void work() {
    cin >> n;
    ans = 0;
    for (int i = 1; i <= n; i++) {
        ll A, B;
        cin >> A >> B;
        D[i] = A + B;
        ans -= B;
    }
    sort(D + 1, D + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        if (i & 1)
            ans += D[i];
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        work();
    return 0;
}
