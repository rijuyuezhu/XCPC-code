// https://www.luogu.com.cn/problem/P5888
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
const int MAXM = 205;
const int MAXK = 1e5 + 5;
const int P = 998244353;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int n, m, k;
struct Need {
    int a, b;
}A[MAXK];
int lsh[MAXK], tot;
void LSH() {
    sort(lsh + 1, lsh + 1 + tot);
    tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(int x) {
    return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
struct Edge {
    int v, nxt;
}e[MAXK];
int head[MAXK], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
int rst, st, f[MAXM][MAXK], g[MAXM];
int main() {
    n = read(), m = read(), k = read();
    for(int i = 1; i <= k; i++) {
        A[i].a = read(), A[i].b = read();
        lsh[++tot] = A[i].a; lsh[++tot] = A[i].b;
    }
    lsh[++tot] = 1;
    LSH();
    for(int i = 1; i <= k; i++) {
        int a = A[i].a, b = A[i].b;
        a = LSH(a), b = LSH(b);
        if(a != b) addedge(b, a);
    }
    rst = n - tot;
    st = LSH(1);
    f[0][st] = 1; g[0] = 1;
    for(int i = 1; i <= m; i++) {
        //calc 0
        f[i][0] = mns(g[i-1], f[i-1][0]);
        g[i] = pls(g[i], mul(f[i][0], rst));
        //calc others
        for(int u = 1; u <= tot; u++) {
            f[i][u] = mns(g[i-1], f[i-1][u]);
            for(int j = head[u]; j; j = e[j].nxt) {
                int v = e[j].v;
                f[i][u] = mns(f[i][u], f[i-1][v]);
            }
            g[i] = pls(g[i], f[i][u]);
        }
    }
    printf("%d\n", f[m][st]);
    return 0;
}
