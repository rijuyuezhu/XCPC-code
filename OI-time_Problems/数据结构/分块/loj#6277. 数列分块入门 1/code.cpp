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
const int MAXN = 50005;
int n, blo;
int val[MAXN], tag[MAXN], bl[MAXN];

void add(int l, int r, int k) {
    for(int i = l; i <= min(r, blo * bl[l]); i++)
        val[i] += k;
    if(bl[l] != bl[r]) {
        for(int i = blo * (bl[r] - 1) + 1; i <= r; i++)
            val[i] += k;
    }
    for(int i = bl[l] + 1; i <= bl[r] - 1; i++)
        tag[i] += k;
}
int main() {
    n = read(); blo = sqrt(n);
    for(int i = 1; i <= n; i++) {
        val[i] = read(); bl[i] = (i - 1) / blo + 1;
    }
    for(int i = 1; i <= n; i++) {
        int opt = read(), l = read(), r = read(), c = read();
        if(opt == 0) {
            add(l, r, c);
        } else {
            printf("%d\n", val[r] + tag[bl[r]]);
        }
    }
    return 0;
}
