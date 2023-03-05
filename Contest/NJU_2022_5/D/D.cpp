#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
using db = double;
const int MAXN = 55;
int n, m;
db f[MAXN], g[MAXN], sf[MAXN], sg[MAXN];
void work(int te) {
    scanf("%d%d", &n, &m);
    printf("Case #%d: ", te);
    if(n == 1) printf("%.6lf ", 1.0);
    else printf("%.6lf ", f[n]);
    if(m == 1) printf("%.6lf\n", 1.0);
    else printf("%.6lf\n", sg[m] / m);
}
int main() {
    f[1] = 0; sg[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        f[i] = (1 + sf[i-1]) / i;
        sf[i] = sf[i-1] + f[i];
        sg[i] = sg[i-1] + f[i];
    }
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) work(i);
    return 0;
}