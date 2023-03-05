#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int MAXN = 1e5 + 5;
const int MAXV = 1e5 + 5;
int n, H[MAXN], A[MAXN], C[MAXN];
ll sufA[MAXN], ans;
int htoc[MAXV], id[MAXN];
bool cmp(int a, int b) {
    return 1ll * C[a] * A[b] < 1ll * C[b] * A[a];
}
void work(int te) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &H[i], &A[i]);
        C[i] = htoc[H[i]];
        id[i] = i;
    }
    sort(id + 1, id + 1 + n, cmp);
    sufA[n+1] = 0;
    for(int i = n; i >= 1; i--) {
        int t = id[i];
        sufA[i] = sufA[i+1] + A[t];
    }
    ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += 1ll * C[id[i]] * sufA[i];
    }
    printf("Case #%d: %lld\n", te, ans);
}
int main() {
    for(int i = 1, num = 1; num < MAXV; i++) {
        for(int j = 1; j <= i; j++)
            if(num < MAXV)
                htoc[num++] = i;
            else break;
    }
    int T; scanf("%d", &T);
    for(int i = 1; i <= T; i++) work(i);
    return 0;
}