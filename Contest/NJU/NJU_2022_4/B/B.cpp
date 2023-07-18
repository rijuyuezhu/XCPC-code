#include<cstdio>
using ll = long long;
const int MAXN = 1e5 + 5;
int n, ans[MAXN];
void work(int l, int r, int st) {  
    if(l > r) return ;
    int m = (l + r) >> 1;
    ans[m] = st;
    work(l, m-1, st+1);
    work(m+1, r, st+1);
}
int main() {
    scanf("%d", &n);
    work(1, n, 1);
    for(int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}