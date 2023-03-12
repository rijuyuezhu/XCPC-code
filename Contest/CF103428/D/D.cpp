#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

constexpr int MAXN = 1e6 + 5;


struct HS {
    int x, y;
    HS(int x = 0, int y = 0) :x(x), y(y) {}
};
int MOD(int v, int p) {return v >= p ? v-p : v;}
const HS M = {1000000033, 1000000097};
const HS B = {233, 188};
HS operator + (HS a, HS b) {return HS(MOD(a.x+b.x, M.x), MOD(a.y+b.y, M.y));}
HS operator - (HS a, HS b) {return HS(MOD(a.x-b.x+M.x, M.x), MOD(a.y-b.y+M.y, M.y));}
HS operator * (HS a, HS b) {return HS(1ll*a.x*b.x%M.x, 1ll*a.y*b.y%M.y);}
bool operator == (HS a, HS b) {return a.x == b.x && a.y == b.y;}
int n;
string s;
HS hs[MAXN], pw[MAXN];
int d[MAXN];

HS GetHS(int l, int r) {
    return hs[r] - hs[l-1] * pw[r-l+1];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    n = s.length();
    pw[0] = HS(1, 1);
    for(int i = 1; i <= n; i++)
        pw[i] = pw[i-1] * B;
    hs[0] = HS(0, 0);
    for(int i = 1; i <= n; i++)
        hs[i] = hs[i-1] * B + HS(s[i-1], s[i-1]);

    for(int p = n/2+1; p < n; p++) {
        if(GetHS(1, n-p) == GetHS(p+1, n))
            d[n-p+1]++, d[p+1]--;
    }
    for(int i = 1; i <= n; i++)
        d[i] += d[i-1];
    int q;
    cin >> q;
    for(int t = 1; t <= q; t++) {
        int k;
        cin >> k;
        cout << d[k] << '\n';
    }
    return 0;
}
