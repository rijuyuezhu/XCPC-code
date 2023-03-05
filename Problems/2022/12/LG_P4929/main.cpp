#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 505;
constexpr int MAXITEM = 5005 + MAXN;
namespace DLX {
    int n, m, tot;
    int U[MAXITEM], D[MAXITEM], L[MAXITEM], R[MAXITEM], row[MAXITEM], col[MAXITEM], siz[MAXN], rh[MAXN];
    int ans[MAXN];
    void init(int _n, int _m) {
        n = _n, m = _m;
        tot = m+1;
        for(int i = 0; i <= m; i++) {
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
            siz[i] = 0;
        }
        for(int i = 1; i <= n; i++)
            rh[i] = -1;
        L[0] = m; R[m] = 0;
    }
    void ins(int r, int c) {
        ++siz[c];
        row[tot] = r;
        col[tot] = c;
        D[tot] = c;
        U[tot] = U[c];
        D[U[c]] = tot;
        U[c] = tot;
        if(rh[r] == -1) {
            rh[r] = L[tot] = R[tot] = tot;
        } else {
            R[tot] = rh[r];
            L[tot] = L[rh[r]];
            R[L[rh[r]]] = tot;
            L[rh[r]] = tot;
        }
        ++tot;
    }
    void del(int c) {
        R[L[c]] = R[c];
        L[R[c]] = L[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --siz[col[j]];
            }
    }
    void res(int c) {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j]) {
                U[D[j]] = D[U[j]] = j;
                ++siz[col[j]];
            }
        R[L[c]] = L[R[c]] = c;
    }
    bool dance(int step) {
        if(R[0] == 0) {
            for(int i = 0; i < step; i++)
                cout << ans[i] << ' ';
            cout << endl;
            return 1;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(siz[i] < siz[c])
                c = i;
        del(c);
        for(int i = D[c]; i != c; i = D[i]) {
            ans[step] = row[i];
            for(int j = R[i]; j != i; j = R[j])
                del(col[j]);
            if(dance(step + 1))
                return 1;
            for(int j = L[i]; j != i; j = L[j])
                res(col[j]);
        }
        res(c);
        return 0;
    }
}
int n, m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    DLX::init(n, m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            int v;
            cin >> v;
            if(v)
                DLX::ins(i, j);
        }
    if(!DLX::dance(0)) {
        cout << "No Solution!" << endl;
    }
    return 0;
}