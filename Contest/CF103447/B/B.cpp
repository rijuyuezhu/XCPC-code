#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN = 1e5 + 5;
constexpr int MAXV = 101;
int n, A[MAXN], minv, maxv;
vector<int> V[MAXV];
struct Seg {
    int l, r;
};
bool operator < (Seg a, Seg b) {
    return a.r < b.r;
}
int check(int v) {
    vector<Seg> seg;
    for(int i = 1; i <= n; i++) {
        int op = v - A[i];
        if(op < minv || op > maxv)
            continue;
        vector<int>::iterator it = upper_bound(V[op].begin(), V[op].end(), i);
        if(it != V[op].end()) {
            seg.push_back({i, *it});
        }
    }
    if(seg.empty()) 
        return 0;
    sort(seg.begin(), seg.end());
    int lst = 0, ans = 0;
    for(auto v : seg) {
        if(v.l > lst) {
            ++ans;
            lst = v.r;
        }
    }
    return 2 * ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    minv = 200;
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
        V[A[i]].push_back(i);
        minv = min(minv, A[i]);
        maxv = max(maxv, A[i]);
    }
    int ans = 0;
    for(int v = 2 * minv; v <= 2 * maxv; v++)
        ans = max(ans, check(v));
    cout << ans << endl;
    return 0;
}
