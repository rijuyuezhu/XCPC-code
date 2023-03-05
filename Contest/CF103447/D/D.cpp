#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAX = 19;
ll P, Q, p10[MAX];
int delp[MAX], nump[MAX], _p, U;
int delq[MAX], numq[MAX], _q, more0;
ll ansx, ansy;


void initdel() {
    for(int i = 0; i <= 9; i++)
        delp[i] = delq[i] = 0;
    more0 = 0;
}
bool equaldel() {
    for(int i = 1; i <= 9; i++)
        if(delp[i] != delq[i])
            return 0;
    return delq[0] <= delp[0] && delp[0] <= delq[0] + more0;
}
void work() {
    cin >> P >> Q;
    ll tmpP = P, tmpQ = Q;
    _p = _q = 0;
    while(tmpP) {
        nump[_p++] = tmpP % 10;
        tmpP /= 10;
    }
    while(tmpQ) {
        numq[_q++] = tmpQ % 10;
        tmpQ /= 10;
    }
    ansx = P, ansy = Q;
    U = 1 << _p;
    for(int S = 0; S < U; S++) {
        initdel();
        ll x = 0;
        int cnt = 0;
        for(int i = 0; i < _p; i++)
            if((S >> i) & 1) {
                x += p10[cnt] * nump[i];
                ++cnt;
            } else {
                delp[nump[i]]++;
            }
        if(x == 0)
            continue;
        __int128 M = (__int128)x * Q;
        if(M % P != 0)
            continue;
        ll y = (ll)(M / P), tmpy = y;
        int tot = 0;
        while(tmpy && tot < _q) {
            int y0 = tmpy % 10;
            while(tot < _q && numq[tot] != y0) {
                delq[numq[tot]]++;
                tot++;
            }
            if(tot >= _q)
                break;
            tmpy /= 10;
            tot++;
        }
        if(tmpy)
            continue;
        while(tot < _q) {
            if(numq[tot] != 0)
                delq[numq[tot]]++;
            else more0++;
            tot++;
        }
        if(equaldel()) {
            if(x < ansx)
                ansx = x, ansy = y;
        }
    }
    cout << ansx << ' ' << ansy << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    p10[0] = 1;
    for(int i = 1; i < MAX; i++)
        p10[i] = p10[i-1] * 10;
    int n;
    cin >> n;
    while(n--)
        work();
    return 0;
}
