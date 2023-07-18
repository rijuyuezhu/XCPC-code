#include <algorithm>
#include <iostream>
using namespace std;
constexpr int MAXN = 1e3 + 5;
constexpr int INF = 0x3f3f3f3f;
int n, m, A[MAXN][MAXN], row[MAXN], col[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= max(n, m); i++)
        row[i] = col[i] = INF;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            cin >> A[i][j];
            row[i] = min(row[i], A[i][j]);
            col[j] = min(col[j], A[i][j]);
        }
    int ans = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(A[i][j] == row[i] && A[i][j] == col[j])
                ans++;
    cout << ans << endl;
    return 0;
}
