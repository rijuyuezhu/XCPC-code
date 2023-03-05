#include <cstdio>
#include <algorithm>
#include <cmath>
#define rg register
const int maxn = 1e5 + 5;
typedef double db;
int n, m;
db jlx[maxn], jly[maxn];
struct trr {
    int l, r, siz;
    db sumx, sumy, sumxx, sumxy, lazx, lazy, tagx, tagy;
    trr() {
        tagx = tagy = 1e18;
        sumx = sumy = sumxx = sumxy = lazx = lazy = 0;
        l = r = siz = 0;
    }
} tr[maxn << 2];
db getsum1(int l, int r) { return (db)(r - l + 1.0) * (l + r) / 2.0; }
db getsum2(int r) { return (db)r * (r + 1.0) * (2.0 * r + 1.0) / 6.0; }
void push_up(int da) {
    tr[da].sumx = tr[da << 1].sumx + tr[da << 1 | 1].sumx;
    tr[da].sumy = tr[da << 1].sumy + tr[da << 1 | 1].sumy;
    tr[da].sumxx = tr[da << 1].sumxx + tr[da << 1 | 1].sumxx;
    tr[da].sumxy = tr[da << 1].sumxy + tr[da << 1 | 1].sumxy;
}
void push_down(int da) {
    if (tr[da].tagx != 1e18 || tr[da].tagy != 1e18) {
        tr[da << 1].tagx = tr[da].tagx;
        tr[da << 1 | 1].tagx = tr[da].tagx;
        tr[da << 1].tagy = tr[da].tagy;
        tr[da << 1 | 1].tagy = tr[da].tagy;
        tr[da << 1].sumx = tr[da].tagx * tr[da << 1].siz + getsum1(tr[da << 1].l, tr[da << 1].r);
        tr[da << 1 | 1].sumx =
            tr[da].tagx * tr[da << 1 | 1].siz + getsum1(tr[da << 1 | 1].l, tr[da << 1 | 1].r);
        tr[da << 1].sumy = tr[da].tagy * tr[da << 1].siz + getsum1(tr[da << 1].l, tr[da << 1].r);
        tr[da << 1 | 1].sumy =
            tr[da].tagy * tr[da << 1 | 1].siz + getsum1(tr[da << 1 | 1].l, tr[da << 1 | 1].r);
        tr[da << 1].sumxx = tr[da << 1].siz * tr[da].tagx * tr[da].tagx +
                            2.0 * tr[da].tagx * getsum1(tr[da << 1].l, tr[da << 1].r) +
                            getsum2(tr[da << 1].r) - getsum2(tr[da << 1].l - 1);
        tr[da << 1 | 1].sumxx = tr[da << 1 | 1].siz * tr[da].tagx * tr[da].tagx +
                                2.0 * tr[da].tagx * getsum1(tr[da << 1 | 1].l, tr[da << 1 | 1].r) +
                                getsum2(tr[da << 1 | 1].r) - getsum2(tr[da << 1 | 1].l - 1);
        tr[da << 1].sumxy = tr[da << 1].siz * tr[da].tagx * tr[da].tagy +
                            (tr[da].tagx + tr[da].tagy) * getsum1(tr[da << 1].l, tr[da << 1].r) +
                            getsum2(tr[da << 1].r) - getsum2(tr[da << 1].l - 1);
        tr[da << 1 | 1].sumxy = tr[da << 1 | 1].siz * tr[da].tagx * tr[da].tagy +
                                (tr[da].tagx + tr[da].tagy) * getsum1(tr[da << 1 | 1].l, tr[da << 1 | 1].r) +
                                getsum2(tr[da << 1 | 1].r) - getsum2(tr[da << 1 | 1].l - 1);
        tr[da].tagx = tr[da].tagy = 1e18;
        tr[da << 1].lazx = tr[da << 1 | 1].lazx = tr[da << 1].lazy = tr[da << 1 | 1].lazy = 0;
    }
    if (tr[da].lazx != 0 || tr[da].lazy != 0) {
        tr[da << 1].lazx += tr[da].lazx;
        tr[da << 1 | 1].lazx += tr[da].lazx;
        tr[da << 1].lazy += tr[da].lazy;
        tr[da << 1 | 1].lazy += tr[da].lazy;
        tr[da << 1].sumxx +=
            2.0 * tr[da].lazx * tr[da << 1].sumx + tr[da << 1].siz * tr[da].lazx * tr[da].lazx;
        tr[da << 1 | 1].sumxx +=
            2.0 * tr[da].lazx * tr[da << 1 | 1].sumx + tr[da << 1 | 1].siz * tr[da].lazx * tr[da].lazx;
        tr[da << 1].sumxy += tr[da << 1].sumx * tr[da].lazy + tr[da << 1].sumy * tr[da].lazx +
                             tr[da << 1].siz * tr[da].lazx * tr[da].lazy;
        tr[da << 1 | 1].sumxy += tr[da << 1 | 1].sumx * tr[da].lazy + tr[da << 1 | 1].sumy * tr[da].lazx +
                                 tr[da << 1 | 1].siz * tr[da].lazx * tr[da].lazy;
        tr[da << 1].sumx += tr[da << 1].siz * tr[da].lazx;
        tr[da << 1 | 1].sumx += tr[da << 1 | 1].siz * tr[da].lazx;
        tr[da << 1].sumy += tr[da << 1].siz * tr[da].lazy;
        tr[da << 1 | 1].sumy += tr[da << 1 | 1].siz * tr[da].lazy;
        tr[da].lazx = tr[da].lazy = 0;
    }
}
void build(int da, int l, int r) {
    tr[da].l = l, tr[da].r = r, tr[da].siz = r - l + 1;
    if (tr[da].l == tr[da].r) {
        tr[da].sumx = jlx[l];
        tr[da].sumy = jly[l];
        tr[da].sumxx = jlx[l] * jlx[l];
        tr[da].sumxy = jlx[l] * jly[l];
        return;
    }
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    build(da << 1, l, mids);
    build(da << 1 | 1, mids + 1, r);
    push_up(da);
}
void ad(int da, int l, int r, db valx, db valy) {
    if (tr[da].l >= l && tr[da].r <= r) {
        tr[da].lazx += valx;
        tr[da].lazy += valy;
        tr[da].sumxx += 2.0 * valx * tr[da].sumx + tr[da].siz * valx * valx;
        tr[da].sumxy += tr[da].sumx * valy + tr[da].sumy * valx + tr[da].siz * valx * valy;
        tr[da].sumx += tr[da].siz * valx;
        tr[da].sumy += tr[da].siz * valy;
        return;
    }
    push_down(da);
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    if (l <= mids)
        ad(da << 1, l, r, valx, valy);
    if (r > mids)
        ad(da << 1 | 1, l, r, valx, valy);
    push_up(da);
}
void xg(int da, int l, int r, db valx, db valy) {
    if (tr[da].l >= l && tr[da].r <= r) {
        tr[da].lazx = 0, tr[da].lazy = 0;
        tr[da].tagx = valx;
        tr[da].tagy = valy;
        tr[da].sumx = valx * tr[da].siz + getsum1(tr[da].l, tr[da].r);
        tr[da].sumy = valy * tr[da].siz + getsum1(tr[da].l, tr[da].r);
        tr[da].sumxx = tr[da].siz * valx * valx + 2.0 * valx * getsum1(tr[da].l, tr[da].r) +
                       getsum2(tr[da].r) - getsum2(tr[da].l - 1);
        tr[da].sumxy = tr[da].siz * valx * valy + (valx + valy) * getsum1(tr[da].l, tr[da].r) +
                       getsum2(tr[da].r) - getsum2(tr[da].l - 1);
        return;
    }
    push_down(da);
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    if (l <= mids)
        xg(da << 1, l, r, valx, valy);
    if (r > mids)
        xg(da << 1 | 1, l, r, valx, valy);
    push_up(da);
}
db cxx(int da, int l, int r) {
    if (tr[da].l >= l && tr[da].r <= r) {
        return tr[da].sumx;
    }
    push_down(da);
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    rg db nans = 0;
    if (l <= mids)
        nans += cxx(da << 1, l, r);
    if (r > mids)
        nans += cxx(da << 1 | 1, l, r);
    return nans;
}
db cxy(int da, int l, int r) {
    if (tr[da].l >= l && tr[da].r <= r) {
        return tr[da].sumy;
    }
    push_down(da);
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    rg db nans = 0;
    if (l <= mids)
        nans += cxy(da << 1, l, r);
    if (r > mids)
        nans += cxy(da << 1 | 1, l, r);
    return nans;
}
db cxxx(int da, int l, int r) {
    if (tr[da].l >= l && tr[da].r <= r) {
        return tr[da].sumxx;
    }
    push_down(da);
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    rg db nans = 0;
    if (l <= mids)
        nans += cxxx(da << 1, l, r);
    if (r > mids)
        nans += cxxx(da << 1 | 1, l, r);
    return nans;
}
db cxxy(int da, int l, int r) {
    if (tr[da].l >= l && tr[da].r <= r) {
        return tr[da].sumxy;
    }
    push_down(da);
    rg int mids = (tr[da].l + tr[da].r) >> 1;
    rg db nans = 0;
    if (l <= mids)
        nans += cxxy(da << 1, l, r);
    if (r > mids)
        nans += cxxy(da << 1 | 1, l, r);
    return nans;
}
db getx(int l, int r) { return (db)cxx(1, l, r) / (r - l + 1); }
db gety(int l, int r) { return (db)cxy(1, l, r) / (r - l + 1); }
void solve(int l, int r) {
    db ans1 = cxxy(1, l, r) - (db)(r - l + 1) * getx(l, r) * gety(l, r);
    db ans2 = cxxx(1, l, r) - (db)(r - l + 1) * getx(l, r) * getx(l, r);
    printf("%.10f\n", ans1 / ans2);
}
int main() {
	freopen("relative.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (rg int i = 1; i <= n; i++) {
        scanf("%lf", &jlx[i]);
    }
    for (rg int i = 1; i <= n; i++) {
        scanf("%lf", &jly[i]);
    }
    build(1, 1, n);
    rg int aa, bb, cc;
    db dd, ee;
    for (rg int i = 1; i <= m; i++) {
        scanf("%d%d%d", &aa, &bb, &cc);
        if (aa == 1) {
            solve(bb, cc);
        } else if (aa == 2) {
            scanf("%lf%lf", &dd, &ee);
            ad(1, bb, cc, dd, ee);
        } else {
            scanf("%lf%lf", &dd, &ee);
            xg(1, bb, cc, dd, ee);
        }
    }
    return 0;
}
