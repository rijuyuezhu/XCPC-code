#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXK = 105;//workers;
const int MAXN = 16005;//planks;
struct Person {
    int l, p, s;
    //len, price, start
}a[MAXN];
bool cmp(const Person& a, const Person& b) {
    return a.s < b.s;
}

int n, k;
int f[MAXK][MAXN];
int que[MAXN], hd, tl;
int main() {
    n = read(), k = read();
    for(int i = 1; i <= k; i++) a[i].l = read(), a[i].p = read(), a[i].s = read();
    sort(a + 1, a + 1 + k, cmp);
    for(int i = 1; i <= k; i++) {
        hd = 1, tl = 0;
        que[++tl] = 0;
        for(int j = 1; j <= n; j++) {
            f[i][j] = max(f[i-1][j], f[i][j-1]);
            if(j < a[i].s) {
                while(hd <= tl && f[i-1][que[tl]] - a[i].p * que[tl] <=f[i-1][j] - a[i].p * j) tl--;
                que[++tl] = j; 
            } else {
                while(hd <= tl && j - a[i].l > que[hd]) hd++;
                if(hd <= tl) f[i][j] = max(f[i][j], f[i-1][que[hd]] - a[i].p * que[hd] + a[i].p * j);
            }
        }
    }
    printf("%d\n", f[k][n]);
    return 0;
}