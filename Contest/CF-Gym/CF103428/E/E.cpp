#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
using ll = long long;
using db = double;
constexpr int MAXN = 1e5 + 5;
constexpr int MAXQ = 1e5 + 5;
constexpr int MAXK = 105;
constexpr db eps = 1e-4;

int n, K, Q, id[MAXN];
ll a[MAXN], suf[MAXN];
db f[MAXK];

bool cmp(int x, int y) {
    return a[x] < a[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> K >> Q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = i;
    }
    sort(id + 1, id + 1 + n, cmp);
    suf[n+1] = 0;
    for(int i = n; i >= 1; i--)
        suf[i] = suf[i+1] + a[id[i]];
    f[0] = 2.0 * suf[1] / n;
    for(int k = 1; k <= K; k++) {
        long long tot = 0, sum = 0;
        int j = n + 1;
        for(int i = 1; i <= n; i++) {
            while(j > i + 1 && a[id[i]] + a[id[j-1]] > f[k-1])
                --j;
            j = max(j, i+1);
            tot += n - j + 1;
            sum += (n - j + 1) * a[id[i]] + suf[j];
        }
        db pro = 2.0 * tot / n / (n-1);
        f[k] = 2.0 * sum / n / (n-1) + (1.0 - pro) * f[k-1];
    }
    cout << fixed << setprecision(10) << f[K] << '\n';

    for(int t = 1; t <= Q; t++) {
        int x, y, c;
        cin >> x >> y >> c;
        db pnt = a[x] +a[y];
        if(abs(pnt - f[c]) < eps)
            cout << "both" << '\n';
        else if(pnt < f[c]) 
            cout << "reselect" << '\n';
        else
            cout << "accept" << '\n';
    }
    return 0;
}
