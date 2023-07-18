#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
constexpr int MAXN = 2e5 + 5;
int n, a[MAXN], b[MAXN], ida[MAXN], idb[MAXN], del[MAXN];
vector<pair<int, int> > ans_array;

bool cmpa(int x, int y) {
    return a[x] > a[y];
}

bool cmpb(int x, int y) {
    return b[x] > b[y];
}

bool check(int haveswap) {
    ll A = 0, B = 0, S = 0;
    for (int i = 1; i <= n; i++) {
        A = max<ll>(A, a[i]);
        S += 1ll * a[i] * b[i];
        ida[i] = idb[i] = i;
        del[i] = 0;
    }
    if (S % A)
        return 0;
    B = S / A;
    sort(ida + 1, ida + 1 + n, cmpa);
    sort(idb + 1, idb + 1 + n, cmpb);
    int cnta = 1, cntb = 1, delnum = 0;
    ll h = A, w = B;
    while (delnum < n) {
        bool isdel = 0;
        while(cnta <= n && (del[ida[cnta]] || a[ida[cnta]] == h)) {
            if(!del[ida[cnta]]) {
                del[ida[cnta]] = 1;
                isdel = 1;
                w -= b[ida[cnta]];
                delnum++;
            }
            cnta++;
        }
        while(cntb <= n && (del[idb[cntb]] || b[idb[cntb]] == w)) {
            if(!del[idb[cntb]]) {
                del[idb[cntb]] = 1;
                isdel = 1;
                h -= a[idb[cntb]];
                delnum++;
            }
            cntb++;
        }
        if(!isdel)
            break;
    }
    if(delnum >= n) {
        if(haveswap)
            swap(A, B);
        ans_array.push_back(make_pair(A, B));
        return 1;
    } else {
        return 0;
    }
}

void work() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];
    ans_array.clear();
    check(0);
    for (int i = 1; i <= n; i++)
        swap(a[i], b[i]);
    check(1);
    int tot = unique(ans_array.begin(), ans_array.end()) - ans_array.begin();
    ans_array.resize(tot);
    cout << tot << '\n';
    for(const auto &pr : ans_array)
        cout << pr.first << ' ' << pr.second << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        work();
    return 0;
}
