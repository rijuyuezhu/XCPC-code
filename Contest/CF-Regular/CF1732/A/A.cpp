#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 25;
int a[MAXN], n;
int gcd(int x, int y) {
    return !y ? x : gcd(y, x % y);
}
void work() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int x = a[1];
    for(int i = 2; i <= n; i++)
        x = gcd(x, a[i]);
    if(x == 1) {
        printf("0\n");
        return ;
    }
    int ans = min(n, 3);
    for(int i = 1; i <= n; i++)
        if(gcd(x, i) == 1) {
            ans = min(ans, n - i + 1);
        }
    printf("%d\n", ans);
    return ;
}
int main() {
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++) work();
    return 0;
}