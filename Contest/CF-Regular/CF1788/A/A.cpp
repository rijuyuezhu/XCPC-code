#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
int n, a[MAXN];
void work() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    int total = 0;
    for(int i = 1; i <= n; i++)
        if(a[i] == 2)
            ++total;
    if(total & 1) {
        cout << -1 << '\n';
    } else {
        int nowcnt = 0;
        for(int i = 1; i <= n; i++) { 
            if(a[i] == 2) {
                ++nowcnt;
            }
            if(nowcnt == total / 2) {
                cout << i << '\n';
                break;
            }
        }
    }
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
