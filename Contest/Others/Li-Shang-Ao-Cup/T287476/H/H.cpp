#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;
int n, s[MAXN], d[MAXN], f[MAXN][3], ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    for(int i = 1; i <= n-1; i++) {
        d[i] = s[i] ^ s[i+1];
    }
    for(int i = 1; i <= n-1; i++) {
        if(d[i]) {
            for(int times = 0; times <= 2; times++) {
                f[i][times] = f[i-1][times] + 1;
            }
        } else {
            for(int times = 0; times <= 2; times++) {
                if(!times)
                    f[i][times] = 0;
                else 
                    f[i][times] = f[i-1][times-1] + 1;
            }
        }
        for(int times = 0; times <= 2; times++)
            ans = max(ans, f[i][times]);
    }
    cout << ans + 1 << endl;
    return 0;
}