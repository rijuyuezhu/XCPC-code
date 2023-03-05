#include <algorithm>
#include <iostream>
using namespace std;

constexpr int MAXN = 1e5 + 5;

int n, A[MAXN];

void work() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> A[i];
    if(A[1] == 0) {
        bool fl = 1;
        for(int i = 1; i <= n; i++)
            if(A[i] != 0) {
                fl = 0;
                break;
            }
        if(fl)
            cout << 1 << '\n';
        else
            cout << -1 << '\n';
        return ;
    } else if(A[1] >= 2) {
        cout << -1 << '\n';
        return ;
    } else { //A[1] == 1
        int M = -1;
        for(int i = 1; i < n; i++) {
            if(2 * A[i] != A[i+1]) {
                M = 2 * A[i] - A[i+1];
                break;
            }
        }
        if(M == -1) {
            cout << -1 << '\n';
            return ;
        }
        int fl = 1;
        for(int i = 1; i < n; i++)
            if(2 * A[i] % M != A[i+1]) {
                fl = 0;
                break;
            }
        if(fl)
            cout << M << '\n';
        else
            cout << -1 << '\n';
    }
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
