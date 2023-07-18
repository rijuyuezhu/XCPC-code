#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 1e5 + 5;
int n, k, A[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> A[i];
    sort(A + 1, A + 1 + n);
    int lst = A[1], tot = 1;
    for(int i = 2; i <= n; i++)
        if(A[i] - lst >= k) {
            lst = A[i];
            tot++;
        }
    cout << tot << endl;
    return 0;
}
