#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 5;

int n;
int a[MAXN], cnt[MAXN];

void clear() {
    for (int i = 0; i <= n; i++)
        cnt[i] = 0;
}

void work() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    clear();
    for (int i = 1; i <= n; i++)
        if (a[i] <= n)
            cnt[a[i]]++;
    int k = -1;
    for (int i = 0; i <= n; i++)
        if (cnt[i] == 0) {
            k = i;
            break;
        }
    int l = n+1, r = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] == k + 1) {
            l = min(l, i);
            r = max(r, i);
        }
    bool flag = 1;
    if (l <= r) {
        for (int i = l; i <= r; i++)
            if (a[i] < k)
                cnt[a[i]]--;
        for (int i = 0; i < k; i++)
            if (cnt[i] == 0) {
                flag = 0;
                break;
            }
    } else if(n == k) {
        flag = 0;
    }
    cout << (flag ? "Yes" : "No") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        work();
    
    return 0;
}
