#include <iostream>
#include <algorithm>
using namespace std;


constexpr int MAXN = 2e5 + 5;
int n, a[MAXN];
void work() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    a[0] = -1; a[n+1] = n+1;
    int ans = 0;
    for(int i = 0; i <= n; i++)
        if(a[i] + 1 <= i && i <= a[i+1] - 1)
            ++ans;
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
