//https://www.luogu.com.cn/problem/P3382
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 15;
const double eps = 1e-7;
int n;
double a[MAXN];//单峰
double l, r;
double f(double x) {
    double ans = 0;
    for(int i = 0; i <= n; i++) ans = ans * x + a[i];
    return ans;
}
int main() {
    n = read();
    scanf("%lf%lf", &l, &r);
    for(int i = 0; i <= n; i++) scanf("%lf", &a[i]);
    while(l + eps < r) {
        double lm = l + (r - l) / 3, lf = f(lm);
        double rm = r - (r - l) / 3, rf = f(rm);
        if(lf < rf) l = lm;
        else r = rm;
    }
    printf("%.5lf\n", l);
    return 0;
}