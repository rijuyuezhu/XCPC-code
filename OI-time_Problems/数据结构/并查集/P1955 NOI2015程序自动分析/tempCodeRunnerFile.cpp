// https://www.luogu.com.cn/problem/P1955
//并查集
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
const int MAXN = 2e6 + 5;
int n;
struct Node {
    int e, a, b;
}con[MAXN];

int lsh[MAXN], tot;
void LSH() {
    sort(lsh + 1, lsh + 1 + tot);
    tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(int x) {
    return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}

int upto[MAXN];
int getup(int u) {
    if(upto[u] == u) return u;
    return upto[u] = getup(upto[u]);
}

void solve() {
    tot = 0;
    n = read();
    for(int i = 1; i <= n; i++) {
        con[i].a = read(), con[i].b = read(), con[i].e = read();
        lsh[++tot] = con[i].a; lsh[++tot] = con[i].b;
    }
    LSH();
    for(int i = 1; i <= tot; i++) upto[i] = i;
    for(int i = 1; i <= n; i++) if(con[i].e == 1) {
        int a = LSH(con[i].a), b = LSH(con[i].b);
        upto[getup(a)] = getup(b);
    }
    for(int i = 1; i <= n; i++) if(con[i].e == 0) {
        int a = LSH(con[i].a), b = LSH(con[i].b);
        if(getup(a) == getup(b)) {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}
int main() {
    int t = read();
    while(t--) solve();
    return 0;
}