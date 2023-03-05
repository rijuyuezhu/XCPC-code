#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 200005;
const double INF = 1e50;
int n;
struct Point {
    double x, y;
}P[MAXN], tmp[MAXN];
double sqr(double x) {return x * x;}
double disqr(const Point& a, const Point& b) {return sqr(b.x - a.x) + sqr(b.y - a.y);}
bool cmp1(const Point& x, const Point& y) {
    return x.x < y.x;
}

int b[MAXN];
void my_merge(int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while(i <= m && j <= r) {
        if(P[i].y < P[j].y) tmp[k++] = P[i++];
        else tmp[k++] = P[j++];
    }
    while(i <= m) tmp[k++] = P[i++];
    while(j <= r) tmp[k++] = P[j++];
    for(int i = l; i <= r; i++) P[i] = tmp[i];
}
double solve(int l, int r) {
    if(l >= r) return INF;
    if(l + 1 == r) {if(P[l].y > P[r].y) swap(P[l], P[r]); return disqr(P[l], P[r]);}
    int mid = (l + r) >> 1, mx = P[mid].x, cnt = 0;
    double d = min(solve(l, mid), solve(mid+1, r));
    my_merge(l, mid, r);
    for(int i = l; i <= r; i++)
        if(sqr(P[i].x - mx) < d) b[++cnt] = i;
    for(int i = 1; i <= cnt; i++)
        for(int j = i + 1; j <= cnt && sqr(P[b[i]].y - P[b[j]].y) < d; j++)
            d = min(d, disqr(P[b[i]], P[b[j]]));
    return d;
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) scanf("%lf%lf", &P[i].x, &P[i].y);
    sort(P + 1, P + n + 1, cmp1);
    printf("%.4lf", sqrt(solve(1, n)));
    return 0;
}
