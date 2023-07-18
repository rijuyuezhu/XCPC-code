#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using pr = pair<int, int>;
constexpr int MAXN = 2e5 + 5;
int n;
struct Rec {
    int u, d, l, r;
}rec[MAXN], ans[MAXN];
constexpr Rec EMPTY = {0, 0, 0, 0};
vector<int> both, single;
vector<pr> cover;
vector<int> pre;
vector<int> st[18];
int area, lg2[MAXN];
bool cmp(int a, int b) {
    return rec[a].r < rec[b].r;
}

int better(int x, int y) {
    return pre[x] < pre[y] ? y : x;//left first.
}

int queryst(int l, int r) {
    int k = lg2[r - l + 1];
    return better(st[k][l], st[k][r - (1 << k) + 1]);
}

int findl(int L) {
    int l = 0, r = cover.size()-1, ans = -1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(cover[m].second >= L) {
            ans = m;
            r = m - 1;
        } else l = m + 1;
    }
    return ans;
}
int findr(int R) {
    int l = 0, r = cover.size()-1, ans = -1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(cover[m].second <= R) {
            ans = m;
            l = m - 1;
        } else r = m + 1;
    }
    return ans;
}
int Lenpr(pr a) {
    return a.second - a.first + 1;
}
void gao() {
    sort(single.begin(), single.end(), cmp);
    int lst = -1;
    for(auto rid : single) {
        pr ret, mid, right;
        ans[rid] = rec[rid];
        ans[rid].l = max(ans[rid].l, lst+1);
        int posl = findl(ans[rid].l);
        int posr = findr(ans[rid].r);
        if(posl == -1 || posr == -1) {
            goto end;
        }
        while(posl < (int)cover.size() && ans[rid].l >= cover[posl].first) {
            ans[rid].l = max(ans[rid].l, cover[posl].second + 1);
            posl++;
        }
        while(posr >= 0 && ans[rid].r <= cover[posr].second) {
            ans[rid].r = min(ans[rid].r, cover[posr].first - 1);
            posr--;
        }
        if(posl >= (int)cover.size() || posr < 0 || posl > posr)
            goto end;
        //left
        ret = {ans[rid].l, cover[posl].first - 1};
        //mid
        if(posl + 1 == posr)
            mid = {0, -1};
        else {
            int choose = queryst(posl + 1, posr);
            mid = {cover[choose-1].second + 1, cover[choose].first - 1};
        }
        if(Lenpr(mid) > Lenpr(ret))
            ret = mid;
        //right
        right = {cover[posr].second + 1, ans[rid].r};
        if(Lenpr(right) > Lenpr(ret))
            ret = mid;
        ans[rid].l = ret.first;
        ans[rid].r = ret.second;

        end:;

        if(ans[rid].l > ans[rid].r) {
            ans[rid] = EMPTY;
        } else {
            lst = ans[rid].r;
        }
    }
}

void work() {
    cover.clear();
    pre.clear();
    both.clear();
    single.clear();
    for(int i = 0; i < 18; i++)
        st[i].clear();
    area = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> rec[i].u >> rec[i].l >> rec[i].d >> rec[i].r;
    for(int i = 1; i <= n; i++)
        if(rec[i].u == 1 && rec[i].d == 2)
            both.push_back(i);
    sort(both.begin(), both.end(), cmp);
    int lst = -1;
    for(auto rid : both) {
        ans[rid] = rec[rid];
        ans[rid].l = max(ans[rid].l, lst+1);
        if(ans[rid].l > ans[rid].r) {
            ans[rid] = EMPTY;
        } else {
            area += (ans[rid].r - ans[rid].l + 1) * 2;
            lst = ans[rid].r;
            cover.push_back({ans[rid].l, ans[rid].r});
        }
    }
    pre.resize(cover.size());
    for(int i = 0; i < (int)cover.size(); i++)
        pre[i] = (i == 0 ? cover[i].first - 1: cover[i].first - cover[i-1].second - 1);
    for(int i = 0; i < 18; i++)
        st[i].resize(cover.size());
    for(int i = 0; i < (int)cover.size(); i++)
        st[0][i] = i;
    for(int k = 1; (1 << k) < (int)cover.size(); k++)
        for(int i = 0; i + (1 << k) - 1 < (int)cover.size(); i++)
            st[k][i] = better(st[k-1][i], st[k-1][i + (1 << (k-1))]);

    single.clear();
    for(int i = 1; i <= n; i++)
        if(rec[i].d == 1)
            single.push_back(i);
    gao();
    single.clear();
    for(int i = 1; i <= n; i++)
        if(rec[i].u == 2)
            single.push_back(i);
    gao();
    cout << area << '\n';
    for(int i = 1; i <= n; i++)
        cout << ans[i].u << ans[i].l << ans[i].d << ans[i].r << '\n';

}

int main() {
    lg2[0] = -1;
    for(int i = 1; i < MAXN; i++)
        lg2[i] = lg2[i >> 1] + 1;
    int t;
    cin >> t;
    while(t--)
        work();
    return 0;
}
